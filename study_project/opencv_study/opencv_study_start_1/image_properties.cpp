/**
 * 获取图像属性
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat image = imread("/home/alnes/Code-base/study_project/opencv_study/opencv_study_start_1/resoures/msg/2.jpg");

    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 获取图像属性
    int width = image.cols;  // 图像宽度
    int height = image.rows; // 图像高度
    int channels = image.channels(); // 图像通道数

    cout << "图像宽度: " << width << endl;
    cout << "图像高度: " << height << endl;
    cout << "图像通道数: " << channels << endl;

    return 0;
}