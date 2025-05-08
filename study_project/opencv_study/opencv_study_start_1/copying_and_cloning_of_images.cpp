/**
 * 图像的复制与克隆
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

    // 复制图像
    Mat copiedImage = image.clone();

    // 修改复制的图像
    circle(copiedImage, Point(100, 100), 50, Scalar(0, 255, 0), 2); // 在复制的图像上画一个圆

    // 显示原始图像和修改后的图像
    imshow("Original Image", image);
    imshow("Copied Image", copiedImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}