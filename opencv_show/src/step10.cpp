#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct LightBar {
    cv::RotatedRect rect;
    cv::Point2f center;
    float width;
    float height;
    float ratio;
    float area;
    float angle;
};

struct ArmorPlate {
    LightBar leftBar;
    LightBar rightBar;
    cv::Point2f center;
    float width;
    float height;
};

std::vector<LightBar> detectLightBars(const cv::Mat &mask,
                                      double minArea, double maxArea,
                                      float minRatio)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<LightBar> bars;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area < minArea || area > maxArea) {
            continue;
        }

        cv::RotatedRect rect = cv::minAreaRect(contours[i]);
        float w = std::min(rect.size.width, rect.size.height);
        float h = std::max(rect.size.width, rect.size.height);
        if (w < 1.0f) {
            continue;
        }

        float ratio = h / w;
        if (ratio < minRatio) {
            continue;
        }

        cv::Point2f p[4];
        rect.points(p);
        cv::Point2f v = p[1] - p[0];
        cv::Point2f e = p[2] - p[1];
        if (v.dot(v) < e.dot(e)) {
            v = e;
        }
        float angle = float(std::atan2(v.y, v.x) * 180.0 / CV_PI);
        angle = std::fmod(angle + 180.0f, 180.0f);

        LightBar bar;
        bar.rect = rect;
        bar.center = rect.center;
        bar.width = w;
        bar.height = h;
        bar.ratio = ratio;
        bar.area = float(area);
        bar.angle = angle;
        bars.push_back(bar);
    }
    return bars;
}

std::vector<ArmorPlate> pairLightBars(const std::vector<LightBar> &bars,
                                      float maxHeightDiff,
                                      float maxAngleDiff,
                                      float maxYOffsetFactor,
                                      float minXGapFactor,
                                      float maxXGapFactor)
{
    std::vector<ArmorPlate> plates;
    for (size_t i = 0; i < bars.size(); ++i) {
        for (size_t j = i + 1; j < bars.size(); ++j) {
            const LightBar *left = &bars[i];
            const LightBar *right = &bars[j];
            if (left->center.x > right->center.x) {
                std::swap(left, right);
            }

            float avgHeight = (left->height + right->height) * 0.5f;
            float heightDiff = std::abs(left->height - right->height)
                             / std::max(left->height, right->height);
            if (heightDiff > maxHeightDiff) {
                continue;
            }

            float d = std::abs(left->angle - right->angle);
            float angleDiff = std::min(d, 180.0f - d);
            if (angleDiff > maxAngleDiff) {
                continue;
            }

            float yOffset = std::abs(left->center.y - right->center.y);
            if (yOffset > avgHeight * maxYOffsetFactor) {
                continue;
            }

            float xGap = right->center.x - left->center.x;
            if (xGap < avgHeight * minXGapFactor ||
                xGap > avgHeight * maxXGapFactor) {
                continue;
            }

            cv::Point2f delta = right->center - left->center;
            float a = float(std::atan2(delta.y, delta.x) * 180.0 / CV_PI);
            if (std::abs(a) > 30.0f) {
                continue;
            }

            ArmorPlate plate;
            plate.leftBar = *left;
            plate.rightBar = *right;
            plate.center = (left->center + right->center) * 0.5f;
            plate.width = xGap;
            plate.height = avgHeight;
            plates.push_back(plate);
        }
    }
    return plates;
}

// 以装甲板中心为起点，取 ROI、找白色数字、与 0～9 模板匹配
int recognizeDigit(const cv::Mat &image, const ArmorPlate &plate,
                   const std::vector<cv::Mat> &templates,
                   double &bestScore)
{
    int cx = cvRound(plate.center.x);
    int cy = cvRound(plate.center.y);
    int halfW = cvRound(plate.width * 0.4f);
    int halfH = cvRound(plate.height * 1.0f);
    // 取 ROI 
    cv::Rect roiRect(cx - halfW, cy - halfH, 2 * halfW, 2 * halfH);
    roiRect &= cv::Rect(0, 0, image.cols, image.rows);
    cv::Mat roi = image(roiRect);

    // 数字是低饱和度的亮白色，灯条和背景会被 S、V 条件排除
    cv::Mat hsv, white;
    cv::cvtColor(roi, hsv, cv::COLOR_BGR2HSV);
    cv::inRange(hsv, cv::Scalar(0, 0, 180), cv::Scalar(179, 60, 255), white);
    cv::morphologyEx(white, white, cv::MORPH_OPEN,
                     cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(white, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    //找到面积最大的轮廓，认为是数字
    cv::Rect digitBox;
    double bestArea = 0.0;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > bestArea) {
            bestArea = area;
            digitBox = cv::boundingRect(contours[i]);
        }
    }
   //失败保护。面积太小，或者数字框太小，认为没有数字
    bestScore = -1.0;
    if (bestArea < 0.01 * roiRect.area() || digitBox.width < 2 || digitBox.height < 2) {
        return -1;
    }

    // 紧贴数字裁剪，再缩放到模板大小
    cv::Mat gray, query;
    cv::cvtColor(roi, gray, cv::COLOR_BGR2GRAY);
    cv::resize(gray(digitBox), query, cv::Size(128, 160));

    int bestDigit = -1;
    for (int d = 0; d < 10; ++d) {
        cv::Mat scoreMap;
        cv::matchTemplate(query, templates[d], scoreMap, cv::TM_CCOEFF_NORMED);
        double score = scoreMap.at<float>(0, 0);
        if (score > bestScore) {
            bestScore = score;
            bestDigit = d;
        }
    }

    // 分数太低说明不像任何一个数字
    if (bestScore < 0.5) {
        return -1;
    }
    return bestDigit;
}

void drawResults(cv::Mat &canvas,
                 const std::vector<LightBar> &bars,
                 const std::vector<ArmorPlate> &plates,
                 const std::vector<int> &digits)
{
    for (size_t i = 0; i < bars.size(); ++i) {
        const LightBar &bar = bars[i];

        cv::Point2f p[4];
        bar.rect.points(p);
        for (int k = 0; k < 4; ++k) {
            cv::line(canvas, p[k], p[(k + 1) % 4], cv::Scalar(255, 0, 0), 4);
        }
        cv::circle(canvas, bar.center, 8, cv::Scalar(0, 255, 0), -1);

        float rad = bar.angle * float(CV_PI) / 180.0f;
        cv::Point2f v(std::cos(rad), std::sin(rad));
        cv::Point2f a = bar.center - v * (bar.height * 0.5f);
        cv::Point2f b = bar.center + v * (bar.height * 0.5f);
        cv::line(canvas, a, b, cv::Scalar(0, 0, 255), 3);
    }

    for (size_t i = 0; i < plates.size(); ++i) {
        const ArmorPlate &plate = plates[i];

        cv::line(canvas, plate.leftBar.center, plate.rightBar.center,
                 cv::Scalar(0, 255, 255), 4);
        cv::circle(canvas, plate.center, 14, cv::Scalar(255, 255, 0), 4);

        std::string label = "Plate " + std::to_string(i + 1);
        if (digits[i] >= 0) {
            label += ": " + std::to_string(digits[i]);
        } else {
            label += ": ?";
        }
        cv::Point pos(int(plate.center.x - 300),
                      std::max(60, int(plate.center.y - plate.height * 1.2f)));
        cv::putText(canvas, label, pos, cv::FONT_HERSHEY_SIMPLEX,
                    2.0, cv::Scalar(255, 255, 0), 4);
    }
}

int main()
{
    cv::Mat image;
    image = cv::imread("red.jpg");
    if (image.empty()) {
        std::cerr << "Failed to read red.jpg\n";
        return 1;
    }

    // 读取 0～9 模板，统一成 128×160
    std::vector<cv::Mat> templates;
    for (int d = 0; d < 10; ++d) {
        //拼路径，to_string() 是 C++11 新增的函数，返回数字的字符串表示
        std::string path = "../templates/" + std::to_string(d) + ".png";
        //灰度读取模板
        cv::Mat t = cv::imread(path, cv::IMREAD_GRAYSCALE);
        if (t.empty()) {
            std::cerr << "Failed to read " << path << "\n";
            return 1;
        }
        cv::resize(t, t, cv::Size(128, 160));
        //放进模板数组
        templates.push_back(t);
    }

    // HSV 红色掩膜
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    cv::Mat lowRed, highRed, mask;
    cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowRed);
    cv::inRange(hsv, cv::Scalar(170, 100, 100), cv::Scalar(179, 255, 255), highRed);
    cv::bitwise_or(lowRed, highRed, mask);

    // 开运算去噪，闭运算补洞
    cv::Mat opened;
    cv::morphologyEx(mask, opened, cv::MORPH_OPEN,
                     cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    cv::Mat closed;
    cv::morphologyEx(opened, closed, cv::MORPH_CLOSE,
                     cv::getStructuringElement(cv::MORPH_RECT, cv::Size(71, 71)));

    std::vector<LightBar> bars = detectLightBars(closed, 1000.0, 200000.0, 1.5f);
    std::vector<ArmorPlate> plates = pairLightBars(bars, 0.4f, 20.0f, 2.5f, 0.3f, 6.0f);

    std::vector<int> digits(plates.size(), -1);
    std::vector<double> scores(plates.size(), -1.0);
    for (size_t i = 0; i < plates.size(); ++i) {
        digits[i] = recognizeDigit(image, plates[i], templates, scores[i]);
    }

    cv::Mat canvas = image.clone();
    drawResults(canvas, bars, plates, digits);

    std::cout << "bars: " << bars.size()
              << ", armors: " << plates.size() << "\n";
    for (size_t i = 0; i < plates.size(); ++i) {
        std::cout << "  plate " << (i + 1)
                  << ": center=(" << plates[i].center.x << ", " << plates[i].center.y << ")"
                  << " digit=" << digits[i]
                  << " score=" << scores[i] << "\n";
    }

    bool saved = cv::imwrite("number_result.png", canvas);
    if (!saved) {
        std::cerr << "Failed to save number_result.png\n";
    } else {
        std::cout << "Saved number_result.png\n";
    }
    return 0;
}
