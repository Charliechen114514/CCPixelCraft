#include "example_common.h"
#include <opencv2/opencv.hpp>
#include <string>
static constexpr const char* path_of_image = "/cvtcolor/image.jpg";

/*
 * This example shows how to convert an image from one color space to another.
 * The example will convert the image from BGR to Grayscale.
 */
int main() {
    std::string path(EXAMPLE_COMMON_PATH);

    path += path_of_image;

    /* imread will load the image from the file system */
    /* commonly, we load the image in 3 channels. as the BGR Format */
    cv::Mat image = cv::imread(path);

    if (image.empty()) {
        std::cerr << "Could not read the image: " << path << std::endl;
        return 1;
    }

    /* resize to a fit size */
    resize_image(image);

    /* cvtColor will convert the image from BGR to Grayscale */
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    cv::imshow("Image", image);
    cv::imshow("Gray Image", gray_image);
    cv::waitKey(0);

    return 0;
}
