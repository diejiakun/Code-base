/**
 * 图像的裁剪与缩放
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

    // 裁剪图像
    Rect roi(100, 100, 200, 200); // (x, y, width, height)
    Mat croppedImage = image(roi);

    // 缩放图像
    Mat resizedImage;
    resize(image, resizedImage, Size(400, 400)); // 缩放到400x400

    // 显示裁剪和缩放后的图像
    imshow("Cropped Image", croppedImage);
    imshow("Resized Image", resizedImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}