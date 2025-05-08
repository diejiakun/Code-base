/**
 * 图像的几何变换
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

    // 旋转图像
    Mat rotatedImage;
    Point2f center(image.cols / 2, image.rows / 2); // 旋转中心
    double angle = 45; // 旋转角度
    double scale = 1.0; // 缩放比例
    Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);
    warpAffine(image, rotatedImage, rotationMatrix, image.size());

    // 显示旋转后的图像
    imshow("Rotated Image", rotatedImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}