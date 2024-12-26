#include "example_common.h"
#include <opencv2/opencv.hpp>
#include <string>

void show_image_in_window(const cv::Mat& image, const char* window_name,
                          const example_waiting_package& package) {
    std::string win_name{window_name};
    cv::imshow(win_name, image);
    if (package.waiting_key == 0) {
        cv::waitKey(0);
    } else {
        while (1) {
            if (cv::waitKey(package.waiting_time) == package.waiting_key) {
                break;
            }
        }
    }
    return;
}

void resize_image(cv::Mat& image, int width, int height) {
    cv::resize(image, image, cv::Size(width, height));
}
