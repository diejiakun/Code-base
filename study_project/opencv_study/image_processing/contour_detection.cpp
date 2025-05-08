/**
 * 轮廓检测
 * 轮廓检测用于提取图像中的对象轮廓。
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

    // 二值化
    Mat binaryImage;
    threshold(grayImage, binaryImage, 127, 255, THRESH_BINARY);

    // 查找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binaryImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // 绘制轮廓
    Mat contourImage = Mat::zeros(image.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        drawContours(contourImage, contours, i, Scalar(0, 255, 0), 2);
    }

    imshow("Original Image", image);
    imshow("Contours", contourImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}