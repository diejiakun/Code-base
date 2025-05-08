/**
 * 自适应阈值化
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

    // 自适应阈值化
    Mat adaptiveBinaryImage;
    adaptiveThreshold(grayImage, adaptiveBinaryImage, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);

    imshow("Original Image", image);
    imshow("Adaptive Binary Image", adaptiveBinaryImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}