/**
 * 形态学操作
 * 形态学操作用于处理图像的形状和结构。
 * 
 * 
 * 腐蚀与膨胀
 * 腐蚀操作可以消除图像中的小物体或细节，使得前景物体变小。
 * 
 * 膨胀操作可以扩大图像中的前景物体，常用于填补前景物体中的空洞。
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

    // 腐蚀操作
    Mat erodedImage;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    erode(binaryImage, erodedImage, kernel);

    // 膨胀操作
    Mat dilatedImage;
    dilate(binaryImage, dilatedImage, kernel);

    imshow("Original Image", image);
    imshow("Eroded Image", erodedImage);
    imshow("Dilated Image", dilatedImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}