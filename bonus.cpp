#include <iostream>
#include <thread>
#include <vector>

#include <opencv2/opencv.hpp>

void TakeVideo(const std::string& filename) {
    using namespace std::chrono_literals;

    cv::Mat frame;
    cv::VideoCapture webcam;

    if (!webcam.open(0)) {
        std::cerr << "Failed to init webcamera" << std::endl;
        exit(1);
    };
    const int Width = webcam.get(cv::CAP_PROP_FRAME_WIDTH);
    const int Height = webcam.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('a', 'v', 'c', '1'), 30.0, {Width, Height});
    if (!writer.isOpened()) {
        std::cerr << "Failed to init writer" << std::endl;
        exit(1);
    }

    for (int i = 0; i < 100; ++i) {
        webcam >> frame;
        cv::imshow("Live", frame);
        writer.write(frame);
        cv::waitKey(35);
    }
    cv::destroyAllWindows();
}

int main() {
    TakeVideo("video.avi");

    cv::VideoCapture file;
    if (!file.open("video.avi")) {
        std::cerr << "Failed to read video" << std::endl;
        return 1;
    }

    int index = 0;
    while (file.isOpened()) {
        cv::Mat frame, gray, grayBGR;
        file.read(frame);
        if (frame.empty()) {
            break;
        }
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::cvtColor(gray, grayBGR, cv::COLOR_GRAY2BGR);
        cv::line(grayBGR, {50, 50}, {400, 450}, {34, 255, 100}, 15);
        cv::rectangle(grayBGR, {50 + 5 * index, 60 + 3 * index}, {300, 100 + index * 5},
                      {32, (double)index, 32}, 10);
        cv::imshow("file", grayBGR);
        cv::waitKey(35);
        ++index;
    }
    return 0;
}
