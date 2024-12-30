#include "example_common.h"
#include <opencv2/opencv.hpp>
#include <string>

class NullVectorException : public std::exception {
    virtual const char* what() const throw() {
        return "The input vector is null. which is not allowed!\n";
    }
};

class Invalid_Layout_Exception : public std::exception {
    virtual const char* what() const throw() {
        return "The layout is invalid, please check the layout\n";
    }
};

class NullImage : public std::exception {
    virtual const char* what() const throw() {
        return "The image is null, which is not allowed!\n";
    }
};

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

static bool inline is_valid_layout(const size_t          image_num,
                                   const display_layout& layout) {
    return layout.horizontal * layout.vertical == image_num;
}

void display_multi_image(std::vector<cv::Mat>& images, const char* window_name,
                         const display_layout&          layout,
                         const example_waiting_package& package) {
    if (images.size() == 0) {
        throw NullVectorException();
    }

    /* aligned as the first image size */
    int width  = images[0].cols;
    int height = images[0].rows;

    /* resize all images to the same size */
    for (auto& image : images) {
        if (image.empty()) throw NullImage();
        resize_image(image, width, height);
    }

    /* concate the images into a bigger one */

    if (!is_valid_layout(images.size(), layout)) {
        throw Invalid_Layout_Exception();
    }

    cv::Mat              result_one;
    std::vector<cv::Mat> horizontal_images;

    for (int i = 0; i < layout.vertical; i++) {
        std::vector<cv::Mat> vertical_images;
        for (int j = 0; j < layout.horizontal; j++) {
            vertical_images.push_back(images[i * layout.horizontal + j]);
        }
        cv::hconcat(vertical_images, result_one);
        horizontal_images.push_back(result_one);
    }

    cv::vconcat(horizontal_images, result_one);

    /* display the result */
    show_image_in_window(result_one, window_name, package);
}
