#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat image;
    image = cv::imread("red.jpg");
    if (image.empty()) {
        std::cerr << "Failed to read red.jpg\n";
        return 1;
    }

    // BGR 转 HSV，H 为 0～179，S、V 为 0～255
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // 红色在色相环首尾相接，H 分两段提取
    cv::Mat lowRed, highRed, mask;
    cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowRed);
    cv::inRange(hsv, cv::Scalar(170, 100, 100), cv::Scalar(179, 255, 255), highRed);

    // 两段掩膜取并集，白色为红色区域
    cv::bitwise_or(lowRed, highRed, mask);

    // 用掩膜保留原图中的红色，其余像素变黑
    cv::Mat red;
    cv::bitwise_and(image, image, red, mask);

    // 保存掩膜和提取结果
    cv::imwrite("mask.png", mask);
    cv::imwrite("red.png", red);

    std::cout << "Saved mask.png, red.png\n";
    return 0;
}
