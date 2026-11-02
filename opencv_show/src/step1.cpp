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

    // 调整显示窗口大小，不改变图像本身。
    cv::namedWindow("Red Armor", cv::WINDOW_NORMAL);
    cv::resizeWindow("Red Armor", 960, 540);
    cv::imshow("Red Armor", image);
    
    cv::imwrite("save.jpg", image);


    cv::waitKey(0); // 按任意键结束。
    return 0;
}
