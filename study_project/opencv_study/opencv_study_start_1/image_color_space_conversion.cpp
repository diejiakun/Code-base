/**
 * 图像颜色空间转换
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

    // 转换为灰度图像
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // 显示灰度图像
    imshow("Gray Image", grayImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}