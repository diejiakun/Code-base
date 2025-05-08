/**
 * 多目标跟踪
 */
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>

int main() {
    // 1. 检查视频路径
    cv::VideoCapture cap("nailang.mp4");
    if (!cap.isOpened()) {
        std::cerr << "Error opening video!" << std::endl;
        return -1;
    }

    // 2. 打印视频信息
    std::cout << "Video width: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "Video height: " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;

    cv::Mat frame;
    cap >> frame;

    // 3. 检查第一帧是否有效
    if (frame.empty()) {
        std::cerr << "Failed to read first frame!" << std::endl;
        return -1;
    }

    // 4. 选择 ROI
    std::vector<cv::Rect> bboxes;
    cv::selectROIs("Select Objects", frame, bboxes);
    if (bboxes.empty()) {
        std::cerr << "No objects selected!" << std::endl;
        return -1;
    }

    // 5. 初始化跟踪器（不再检查 init() 返回值）
    std::vector<cv::Ptr<cv::Tracker>> trackers;
    for (const auto& bbox : bboxes) {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerCSRT::create();
        tracker->init(frame, bbox);  // init() 返回 void，不能直接 if (!init())
        trackers.push_back(tracker);
    }

    // 6. 主循环
    while (true) {
        bool success = cap.read(frame);
        if (!success || frame.empty()) {
            std::cerr << "End of video or read error!" << std::endl;
            break;
        }

        // 7. 更新跟踪器并绘制结果
        for (auto& tracker : trackers) {
            cv::Rect bbox;
            if (tracker->update(frame, bbox)) {  // update() 返回 bool，可以检查
                cv::rectangle(frame, bbox, cv::Scalar(255, 0, 0), 2);
            }
        }

        cv::imshow("Tracking", frame);
        if (cv::waitKey(30) == 27) break; // 按 ESC 退出
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}