#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 加载微笑检测的 Haar 级联分类器
    CascadeClassifier smileCascade;
    if (!smileCascade.load("haarcascade_smile.xml")) {
        cout << "错误：无法加载微笑检测的 Haar 级联分类器！" << endl;
        return -1;
    }

    // 打开摄像头
    VideoCapture cap("/home/alnes/Code-base/study_project/opencv_study/Actual_combat/kunkun.mp4");
    if (!cap.isOpened()) {
        cout << "错误：无法打开摄像头！" << endl;
        return -1;
    }

    // 实时检测微笑
    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // 转换为灰度图像
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 检测微笑（适当调整检测参数，如 minSize 等）
        vector<Rect> smiles;
        smileCascade.detectMultiScale(gray, smiles, 1.1, 5, 0, Size(20, 20));

        // 绘制检测结果
        for (const auto& smile : smiles) {
            rectangle(frame, smile, Scalar(0, 255, 0), 2);
        }

        // 显示结果
        imshow("Smile Detection", frame);

        // 按下 ESC 键退出
        if (waitKey(30) == 27) break;
    }

    // 释放资源
    cap.release();
    destroyAllWindows();

    return 0;
}