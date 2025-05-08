/**
 * 图像滤波
 * 图像滤波用于去除噪声或增强图像特征。
 * 
 * 
 * 均值滤波
 * 均值滤波是一种简单的线性滤波方法，它将图像中每个像素的值替换为其邻域内所有像素值的平均值。\
 * 这种方法可以有效去除噪声，但也会使图像变得模糊。
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

    // 均值滤波
	//size里面的值越小越清晰，越大越模糊
    Mat blurredImage;
    blur(image, blurredImage, Size(5, 5)); // 5x5 的核

    imshow("Original Image", image);
    imshow("Blurred Image", blurredImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}