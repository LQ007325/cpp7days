#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

// 一条灯条的几何信息
struct LightBar {
    cv::RotatedRect rect;
    cv::Point2f center;
    float width;   // 短边
    float height;  // 长边
    float ratio;   // 长宽比
    float area;
    float angle;   // 长轴角，统一到 [0, 180)
};

// 一对灯条构成的装甲板候选
struct ArmorPlate {
    LightBar leftBar;
    LightBar rightBar;
    cv::Point2f center;
    float width;   // 两灯条中心的水平间距
    float height;  // 两灯条长边的平均值
};

// 从二值掩膜里提取灯条
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

        // 取较长的一条邻边，算长轴角并归一到 [0, 180)
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

// 两两配对，几何约束全部通过才保留
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

            // 高度相近
            float avgHeight = (left->height + right->height) * 0.5f;
            float heightDiff = std::abs(left->height - right->height)
                             / std::max(left->height, right->height);
            if (heightDiff > maxHeightDiff) {
                continue;
            }

            // 方向相近，注意角度是 180 度周期的
            float d = std::abs(left->angle - right->angle);
            float angleDiff = std::min(d, 180.0f - d);
            if (angleDiff > maxAngleDiff) {
                continue;
            }

            // 上下偏移不超过平均高度的若干倍
            float yOffset = std::abs(left->center.y - right->center.y);
            if (yOffset > avgHeight * maxYOffsetFactor) {
                continue;
            }

            // 水平间距在平均高度的范围内
            float xGap = right->center.x - left->center.x;
            if (xGap < avgHeight * minXGapFactor ||
                xGap > avgHeight * maxXGapFactor) {
                continue;
            }

            // 两中心连线的倾角不能太大
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

// 画灯条框、中心、方向线、配对线和装甲板编号
void drawResults(cv::Mat &canvas,
                 const std::vector<LightBar> &bars,
                 const std::vector<ArmorPlate> &plates)
{
    for (size_t i = 0; i < bars.size(); ++i) {
        const LightBar &bar = bars[i];

        cv::Point2f p[4];
        bar.rect.points(p);
        for (int k = 0; k < 4; ++k) {
            cv::line(canvas, p[k], p[(k + 1) % 4], cv::Scalar(255, 0, 0), 4);
        }
        cv::circle(canvas, bar.center, 8, cv::Scalar(0, 255, 0), -1);

        // 沿长轴画红色方向线
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
        cv::Point pos(int(plate.center.x + 24), int(plate.center.y - 24));
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

    // HSV 红色掩膜
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    cv::Mat lowRed, highRed, mask;
    cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowRed);
    cv::inRange(hsv, cv::Scalar(170, 100, 100), cv::Scalar(179, 255, 255), highRed);
    cv::bitwise_or(lowRed, highRed, mask);

    // 开运算去噪，闭运算补洞
    cv::Mat openKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat opened;
    cv::morphologyEx(mask, opened, cv::MORPH_OPEN, openKernel);

    cv::Mat closeKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(71, 71));
    cv::Mat closed;
    cv::morphologyEx(opened, closed, cv::MORPH_CLOSE, closeKernel);

    // 检测灯条和装甲板候选
    std::vector<LightBar> bars = detectLightBars(closed, 1000.0, 200000.0, 1.5f);
    std::vector<ArmorPlate> plates = pairLightBars(bars, 0.4f, 20.0f, 2.5f, 0.3f, 6.0f);

    cv::Mat canvas = image.clone();
    drawResults(canvas, bars, plates);

    std::cout << "bars: " << bars.size()
              << ", armors: " << plates.size() << "\n";
    for (size_t i = 0; i < plates.size(); ++i) {
        std::cout << "  plate " << (i + 1)
                  << ": center=(" << plates[i].center.x
                  << ", " << plates[i].center.y << ")"
                  << " width=" << plates[i].width
                  << " height=" << plates[i].height << "\n";
    }

    bool saved = cv::imwrite("result_detection.png", canvas);
    if (!saved) {
        std::cerr << "Failed to save result_detection.png\n";
    } else {
        std::cout << "Saved result_detection.png\n";
    }
    return 0;
}
