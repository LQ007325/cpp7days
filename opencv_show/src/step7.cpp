#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

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

    // 提取最外层轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(closed, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat result = image.clone();
    int count = 0;

    for (size_t i = 0; i < contours.size(); ++i) {
        // 面积筛选：太小是噪点，太大可能是整块装甲板
        double area = cv::contourArea(contours[i]);
        if (area < 1000 || area > 200000) {
            continue;
        }

        // 最小外接旋转矩形
        cv::RotatedRect rect = cv::minAreaRect(contours[i]);
        //返回的 rect.size.width、rect.size.height 是长宽
        float w = std::min(rect.size.width, rect.size.height);
        float h = std::max(rect.size.width, rect.size.height);
        //确保短边够长
        if (w < 1.0f) {
            continue;
        }

        // 长宽比筛选：灯条是细长的
        float ratio = h / w;
        if (ratio < 1.5f) {
            continue;
        }

        // 统一成“长边相对竖直方向”的倾角，两条灯条才好比较，angle 长边相对竖直方向的角度
        float tilt = (rect.size.width >= rect.size.height)
                         ? 90.0f - rect.angle
                         : rect.angle;

        // 画旋转矩形和中心点
        cv::Point2f vertices[4];
        rect.points(vertices);
        for (int j = 0; j < 4; ++j) {
            cv::line(result, vertices[j], vertices[(j + 1) % 4],
                     cv::Scalar(0, 255, 0), 4);
        }
        // 半径 8 的红色圆点。-1 表示填充圆
        cv::circle(result, rect.center, 8, cv::Scalar(0, 0, 255), -1);

        ++count;
        std::cout << "bar " << count
                  << ": area=" << area
                  << " size=" << w << "x" << h
                  << " ratio=" << ratio
                  << " tilt=" << tilt << "\n";
    }

    std::cout << "bars: " << count << "\n";
    cv::imwrite("bars.png", result);
    std::cout << "Saved bars.png\n";
    return 0;
}
