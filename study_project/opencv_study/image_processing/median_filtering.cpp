/**
 * 中值滤波
 * 中值滤波是一种非线性滤波方法，它将图像中每个像素的值替换为其邻域内所有像素值的中值。这种方法在去除椒盐噪声时效果非常好。
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

    // 中值滤波
    Mat medianBlurredImage;
    medianBlur(image, medianBlurredImage, 5); // 核大小为 5

    imshow("Original Image", image);
    imshow("Median Blurred Image", medianBlurredImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}