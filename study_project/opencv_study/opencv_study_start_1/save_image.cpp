#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat image = imread("/mnt/hgfs/Ubuntu_public/opencv_study/2.jpg");

    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 保存图像
	//该函数的第一个参数是保存文件的路径，第二个参数是要保存的图像。路径后面要给图像起个名
    bool isSaved = imwrite("/home/alnes/Code-base/study_project/opencv_study/opencv_study_start_1/resoures/msg/2.jpg", image);
    if (isSaved) {
        cout << "图像保存成功！" << endl;
    } else {
        cout << "图像保存失败！" << endl;
    }

    return 0;
}