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
    //灰度化
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    //二值化
    cv::Mat binary;
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);
    //BGR三通道分离
    cv::Mat ch[3];
    cv::split(image, ch);

    // BGR 转 HSV
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // HSV 三通道分离
    cv::Mat hsvCh[3];
    cv::split(hsv, hsvCh);

    // 保存九张结果图，格式由扩展名决定
    cv::imwrite("gray.png", gray);
    cv::imwrite("binary.png", binary);
    cv::imwrite("b.png", ch[0]);
    cv::imwrite("g.png", ch[1]);
    cv::imwrite("r.png", ch[2]);
    cv::imwrite("hsv.png", hsv);
    cv::imwrite("h.png", hsvCh[0]);
    cv::imwrite("s.png", hsvCh[1]);
    cv::imwrite("v.png", hsvCh[2]);

    std::cout << "Saved gray.png, binary.png, b.png, g.png, r.png, "
                 "hsv.png, h.png, s.png, v.png\n";
    return 0;
}
