/**
 * 视频监控与运动检测
 */
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap("/home/alnes/Code-base/study_project/opencv_study/Actual_combat/kunkun.mp4");
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream" << std::endl;
        return -1;
    }

    cv::Mat frame, prevFrame, diffFrame;
    cap >> prevFrame;
    cv::cvtColor(prevFrame, prevFrame, cv::COLOR_BGR2GRAY);

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        cv::absdiff(grayFrame, prevFrame, diffFrame);
        cv::threshold(diffFrame, diffFrame, 30, 255, cv::THRESH_BINARY);

        cv::imshow("Motion Detection", diffFrame);
        if (cv::waitKey(1) == 27) break; // ESC key to exit

        prevFrame = grayFrame.clone();
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}