#include "example_common.h"
#include <opencv2/opencv.hpp>
#include <string>
static constexpr const char* path_of_image = "/imread/image.jpg";

int main() {
    std::string path(EXAMPLE_COMMON_PATH);

    path += path_of_image;

    /* imread will load the image from the file system */
    /* commonly, we load the image in 3 channels. as the BGR Format */
    cv::Mat image = cv::imread(path);

    /* resize to a fit size */
    resize_image(image);

    if (image.empty()) {
        std::cerr << "Could not read the image: " << path << std::endl;
        return 1;
    }

    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;
}
