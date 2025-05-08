/**
 * 高斯滤波
 * 高斯滤波是一种非线性滤波方法，它使用高斯函数来计算邻域内像素的权重，\
 * 从而对图像进行平滑处理。高斯滤波在去除噪声的同时，能够更好地保留图像的边缘信息。
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("/home/alnes/Code-base/study_project/opencv_study/image_processing/resoures/msg/2.jpg");
    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 高斯滤波
    Mat gaussianBlurredImage;
    GaussianBlur(image, gaussianBlurredImage, Size(5, 5), 0); // 5x5 的核

    imshow("Original Image", image);
    imshow("Gaussian Blurred Image", gaussianBlurredImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}