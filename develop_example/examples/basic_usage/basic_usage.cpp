/*
    This is the start example of C++ Opencv Tutorial
    Demo aims to introduce the usage of cv::Mat, all the eventual display
    will use cv::imshow to see the image display as direct

    Author: Charliechen114154
    Data:   2024.12.30 Monday

    This example will show the basic usage of cv::Mat, including:
        clone Image
        copy Image
        display the Image ROI
        creating the Mat in a simple way
        browse the common data structure except the cv::Mat

    notes:
    1.  if you are interested in the image display, please refer to the
            example/imread.cpp
    2.  resize function is the same as you can see, it's simple to understand as
        it simply resize the image to the wishing size u provided :)
    3.  opencv/samples/cpp/tutorial_code/core/
        mat_the_basic_image_container/mat_the_basic_image_container.cpp
        is the official example of the basic usage of cv::Mat and other common
        data structure
*/
#include "example_common.h"
#include <iostream>
#include <opencv2/opencv.hpp>

// Experiment implementations
void make_copy_experiment(cv::Mat& image);
void make_roi_experiment(cv::Mat& image);
void simple_mat_creation_experiment();
void other_interesting_data_structure();

cv::Mat get_image_read() {
    std::string base_path(EXAMPLE_COMMON_PATH);
    base_path += "/basic_usage/image.jpg";
    std::cout << "reading image of: " << base_path;
    auto result = cv::imread(base_path);
    resize_image(result, 600, 480);
    return result;
}

int main() {
    cv::Mat image = get_image_read();
    if (image.empty()) {
        std::cerr << "Could not read the image, check the path" << std::endl;
        return 1;
    }
    std::cout << "image load sucess, press q to continue the display";
    // show_image_in_window(image, "the original_image", {'q', 0});

    // make_copy_experiment(image);

    // make_roi_experiment(image);

    // simple_mat_creation_experiment();

    other_interesting_data_structure();

    return 0;
}

void make_copy_experiment(cv::Mat& image) {
    std::cout << "Program will display the cv::Mat copy\n";

    cv::Mat from_copy_assign(image);
    cv::Mat from_operator = image;

    std::vector<cv::Mat> containers;

    containers.push_back(image);
    containers.push_back(from_copy_assign);
    containers.push_back(from_operator);

    display_multi_image(containers, "the copied_images", {3, 1}, {'q', 0});

    std::cout << "This is the same image actually, but referenced by different "
                 "names\n";
    std::cout
        << "You can check the reference count of the images in debuging mode\n";

    std::cout << "We can also create a brand new copy!";
    cv::Mat completely_new = image.clone();
    containers.push_back(completely_new);
    display_multi_image(containers, "the copied_images", {2, 2}, {'q', 0});
    std::cout << "This method create a brand new instead of onlying copying "
                 "the header";
}

void make_roi_experiment(cv::Mat& image) {
    /* We can fetch the ROI area by using the partial-initialization */
    std::cout << "Program will display the cv::Mat ROI operations\n";
    cv::Mat rangeA(image, cv::Rect(10, 10, 100, 100));
    show_image_in_window(rangeA, "ROI Example 1", {'q', 0});

    cv::Mat rangeB = image(cv::Range::all(), cv::Range(1, 200));
    show_image_in_window(rangeB, "ROI Example 2", {'q', 0});
}

void simple_mat_creation_experiment() {
    std::cout << "Creating a image of 2 x 2 (0, 0, 255) Image";
    cv::Mat simple_image(2, 2, CV_8UC3, cv::Scalar(0, 0, 255));
    std::cout << "Opencv Implement the override function of the "
              << "ofstream to display the cv::Mat\n";
    std::cout << simple_image;  // will not be an error!

    cv::Mat actually_is(200, 200, CV_8UC3, cv::Scalar(0, 0, 255));
    show_image_in_window(actually_is, "Brand Red Image", {'q', 0});

    int     sz[3] = {2, 2, 2};
    cv::Mat L(3, sz, CV_8UC(1), cv::Scalar::all(0));
    std::cout << "See the 3D Mat: \n" << L << std::endl;

    std::cout << "Also, we can initalize the Mat as Matlab way";
    cv::Mat E = cv::Mat::eye(4, 4, CV_64F);
    std::cout << "E = " << std::endl << " " << E << std::endl << std::endl;
    cv::Mat O = cv::Mat::ones(2, 2, CV_32F);
    std::cout << "O = " << std::endl << " " << O << std::endl << std::endl;
    cv::Mat Z = cv::Mat::zeros(3, 3, CV_8UC1);
    std::cout << "Z = " << std::endl << " " << Z << std::endl << std::endl;
}

void other_interesting_data_structure() {
    cv::Point2f     pt(0, 0);
    cv::Point3f     pt3(0, 0, 0);
    cv::Size        sz(10, 10);
    cv::Rect        rect(0, 0, 100, 100);
    cv::Scalar      color(255, 0, 0);
    cv::Range       range(0, 10);
    cv::Vec<int, 3> vec(0, 0, 0);
    cv::Vec3b       vec3b(0, 0, 0);
    cv::Vec3f       vec3f(0, 0, 0);
    cv::Vec3d       vec3d(0, 0, 0);

    // you can display them
    std::cout << "pt = " << pt << std::endl;
    std::cout << "pt3 = " << pt3 << std::endl;
    std::cout << "sz = " << sz << std::endl;
    std::cout << "rect = " << rect << std::endl;
    std::cout << "color = " << color << std::endl;
    std::cout << "range = " << range << std::endl;
    std::cout << "vec = " << vec << std::endl;
    std::cout << "vec3b = " << vec3b << std::endl;
    std::cout << "vec3f = " << vec3f << std::endl;
    std::cout << "vec3d = " << vec3d << std::endl;
}
