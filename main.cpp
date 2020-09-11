#include <iostream>
#include <thread>

#include <opencv2/opencv.hpp>

cv::Mat TakePhoto() {
    using namespace std::chrono_literals;

    cv::Mat frame;
    cv::VideoCapture webcam;

    if (!webcam.open(0)) {
        std::cerr << "Failed to init webcamera" << std::endl;
        exit(1);
    };

    std::this_thread::sleep_for(200ms);
    webcam >> frame;
    return frame;
}

void ShowPhoto(const cv::Mat& frame, const std::string& window_name) {
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::imshow(window_name, frame);
    cv::resizeWindow(window_name, 640, 480);
}

int main() {
    auto photo = TakePhoto();
    ShowPhoto(photo, "First");
    cv::moveWindow("First", 10, 100);
    cv::imwrite("photo.jpg", photo);

    std::cout << "Reading photo from disk..." << std::endl;
    photo = cv::imread("photo.jpg");
    if (photo.empty()) {
        std::cerr << "Failed to read from disk" << std::endl;
        return 1;
    }
    cv::Mat gray;
    cv::cvtColor(photo, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, photo, cv::COLOR_GRAY2BGR);
    cv::line(photo, cv::Point(228, 20), cv::Point(402, 220), CV_RGB(100, 40, 50), 15);
    cv::circle(photo, cv::Point(300, 300), 50, CV_RGB(30, 13, 130), 10);
    ShowPhoto(photo, "Second");
    cv::moveWindow("Second", 520, 100);
    cv::waitKey();
    return 0;
}
