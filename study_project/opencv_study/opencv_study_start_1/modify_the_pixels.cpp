/**
 * 访问和修改像素值
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

    // 访问像素值（BGR格式）
    Vec3b pixel = image.at<Vec3b>(100, 100); // 获取(100, 100)位置的像素值
    cout << "B: " << (int)pixel[0] << ", G: " << (int)pixel[1] << ", R: " << (int)pixel[2] << endl;

    // 修改像素值
	int i=100;
	while(--i)
	{
		image.at<Vec3b>(i, i) = Vec3b(255, 0, 0); // 将(--i, --i)位置的像素设置为蓝色
	}
    

    // 显示修改后的图像
    imshow("Modified Image", image);
    waitKey(0);
    destroyAllWindows();

    return 0;
}