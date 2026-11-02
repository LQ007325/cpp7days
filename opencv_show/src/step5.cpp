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

    // 先按 step3 的方法得到红色掩膜
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    cv::Mat lowRed, highRed, mask;
    cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowRed);
    cv::inRange(hsv, cv::Scalar(170, 100, 100), cv::Scalar(179, 255, 255), highRed);
    cv::bitwise_or(lowRed, highRed, mask);

    // 开运算：核要比小白点大、比灯条细，去掉零散噪点
    cv::Mat smallKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat opened;
    cv::morphologyEx(mask, opened, cv::MORPH_OPEN, smallKernel);

    // 闭运算：先膨胀再腐蚀，核要跨过灯条中间约 60 像素宽的空洞
    cv::Mat bigKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(71, 71));
    cv::Mat closed;
    cv::morphologyEx(opened, closed, cv::MORPH_CLOSE, bigKernel);

    // 用处理后的掩膜抠出完整灯条
    cv::Mat redFinal;
    cv::bitwise_and(image, image, redFinal, closed);

    // 保存开运算、闭运算的掩膜和最终结果
    cv::imwrite("mask.png", mask);
    cv::imwrite("opened.png", opened);
    cv::imwrite("closed.png", closed);
    cv::imwrite("red_final.png", redFinal);

    std::cout << "Saved mask.png, opened.png, closed.png, red_final.png\n";
    return 0;
}
