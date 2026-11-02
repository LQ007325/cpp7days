#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Bar {
    cv::RotatedRect rect;
    cv::Rect box;
    double area;
    float ratio;
    float tilt;
};

int main()
{
    cv::Mat image;
    image = cv::imread("red.jpg");
    if (image.empty()) {
        std::cerr << "Failed to read red.jpg\n";
        return 1;
    }

    // 红色掩膜
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

    // 提取轮廓并筛出灯条
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(closed, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<Bar> bars;
    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area < 1000 || area > 200000) {
            continue;
        }

        cv::RotatedRect rect = cv::minAreaRect(contours[i]);
        float w = std::min(rect.size.width, rect.size.height);
        float h = std::max(rect.size.width, rect.size.height);
        if (w < 1.0f) {
            continue;
        }

        float ratio = h / w;
        if (ratio < 1.5f) {
            continue;
        }

        Bar bar;
        bar.rect = rect;
        bar.box = cv::boundingRect(contours[i]);
        bar.area = area;
        bar.ratio = ratio;
        bar.tilt = (rect.size.width >= rect.size.height)
                       ? 90.0f - rect.angle
                       : rect.angle;
        bars.push_back(bar);
    }

    // 先画出所有灯条
    cv::Mat result = image.clone();
    for (size_t i = 0; i < bars.size(); ++i) {
        cv::Point2f vertices[4];
        bars[i].rect.points(vertices);
        for (int j = 0; j < 4; ++j) {
            cv::line(result, vertices[j], vertices[(j + 1) % 4],
                     cv::Scalar(0, 255, 0), 4);
        }
        cv::circle(result, bars[i].rect.center, 8, cv::Scalar(0, 0, 255), -1);
    }

    // 两两配对，长度、倾角、高度和间距都接近才认为是同一块装甲板
    int pairs = 0;
    for (size_t i = 0; i < bars.size(); ++i) {
        for (size_t j = i + 1; j < bars.size(); ++j) {
            const Bar &a = bars[i];
            const Bar &b = bars[j];

            float lenA = std::max(a.rect.size.width, a.rect.size.height);
            float lenB = std::max(b.rect.size.width, b.rect.size.height);
            float avgLen = (lenA + lenB) * 0.5f;
               // 倾角差、长度差、中心点间距，abs()取绝对值
            float angleDiff = std::abs(a.tilt - b.tilt);
            //归一化处理，绝对差变相对差
            //为什么需要lendiff？因为同一装甲版的两灯条长度差不会太大，如果使用绝对差，长度越长，差值就越大，可能会误判
            float lenDiff = std::abs(lenA - lenB) / std::max(lenA, lenB);
            float dx = std::abs(a.rect.center.x - b.rect.center.x);
            float dy = std::abs(a.rect.center.y - b.rect.center.y);

            if (angleDiff > 10.0f) {
                continue;
            }
            if (lenDiff > 0.3f) {
                continue;
            }
            if (dy > 0.5f * avgLen) {
                continue;
            }
            if (dx < 1.0f * avgLen || dx > 4.0f * avgLen) {
                continue;
            }

            // 配对连线 + 装甲板候选框
            cv::line(result, a.rect.center, b.rect.center,
                     cv::Scalar(0, 255, 255), 4);
                     //把两个灯条的轴对齐外接框合并成一个大框，并画成蓝色装甲板候选框
            cv::Rect armor = a.box | b.box;
            cv::rectangle(result, armor, cv::Scalar(255, 0, 0), 5);

            ++pairs;
            std::cout << "armor " << pairs
                      << ": bar " << (i + 1) << " + bar " << (j + 1)
                      << " dx=" << dx << " dy=" << dy
                      << " angleDiff=" << angleDiff
                      << " lenDiff=" << lenDiff << "\n";
        }
    }

    std::cout << "bars: " << bars.size()
              << ", armors: " << pairs << "\n";
    cv::imwrite("armor.png", result);
    std::cout << "Saved armor.png\n";
    return 0;
}
