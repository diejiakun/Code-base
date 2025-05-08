/**
 * 边缘检测
 * 边缘检测用于提取图像中的边缘信息。
 * 
 * Canny 边缘检测
 * Canny 边缘检测是一种多阶段的边缘检测算法，它能够有效地检测出图像中的边缘，并且对噪声具有较强的鲁棒性
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

    // 转换为灰度图像
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Canny 边缘检测
    Mat edges;
    Canny(grayImage, edges, 100, 200); // 阈值1和阈值2

    imshow("Original Image", image);
    imshow("Canny Edges", edges);
    waitKey(0);
    destroyAllWindows();

    return 0;
}