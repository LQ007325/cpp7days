#include <opencv2/opencv.hpp>
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

    // 只取最外层轮廓，灯条内部的空洞不用管
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(closed, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 在原图上画出绿色轮廓
    cv::Mat result = image.clone();
    // -1 表示画出所有轮廓，绿色，线宽 4
    cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0), 4);

    std::cout << "contours: " << contours.size() << "\n";
    for (size_t i = 0; i < contours.size(); ++i) {
        std::cout << "  contour " << i
                  << " area = " << cv::contourArea(contours[i]) << "\n";
    }

    cv::imwrite("closed.png", closed);
    cv::imwrite("contours.png", result);

    std::cout << "Saved closed.png, contours.png\n";
    return 0;
}
