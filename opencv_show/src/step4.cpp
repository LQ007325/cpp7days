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

    // 灯条中间过曝成白色，掩膜里留下约 60 像素宽的空洞，
    // 结构元素要比这个空洞大，才能一次把它补上。
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(71, 71));

    // 膨胀：白色区域向外扩，把灯条中间的空洞填掉
    cv::Mat dilated;
    cv::dilate(mask, dilated, kernel);

    // 腐蚀：外轮廓再缩回原来的大小
    cv::Mat filled;
    cv::erode(dilated, filled, kernel);

    // 用补好的掩膜把完整灯条抠出来
    cv::Mat redFull;
    cv::bitwise_and(image, image, redFull, filled);

    // 保存补洞前后的掩膜和最终红色灯条
    cv::imwrite("mask.png", mask);
    cv::imwrite("dilated.png", dilated);
    cv::imwrite("filled.png", filled);
    cv::imwrite("red_full.png", redFull);

    std::cout << "Saved mask.png, dilated.png, filled.png, red_full.png\n";
    return 0;
}
