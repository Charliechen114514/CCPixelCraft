/*
    This is for beginners of the OpenCV library.
    If you finished your work in installing the opencv library
    You can try building and running the example

    Author: Charliechen114514
    Date:   2024/12/30
*/

#include "example_common.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

std::string make_up_example_path() {
    /* don't worry,  EXAMPLE_COMMON_PATH points to the base dir of the
     * example!*/
    return std::string(EXAMPLE_COMMON_PATH) + "/beginners/image.jpg";
}

int main() {
    auto image_path = make_up_example_path();
    Mat  img        = imread(image_path, IMREAD_COLOR);

    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    imshow("Display window", img);
    std::cout << "Press 's' to save the image" << std::endl;
    int k = waitKey(0);  // Wait for a keystroke in the window

    if (k == 's') {
        bool result = imwrite("You success!.png", img);
        if (result) {
            std::cout << "Image saved successfully, see your building "
                         "directory to check the result"
                      << std::endl;
        } else {
            std::cerr << "Could not save the image" << std::endl;
        }
    }

    return 0;
}
