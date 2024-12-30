# Start from 0  

​	As we all know, opencv is an important library for image processing. In OpenCV 4, we have multiple modules. Each module is responsible for a different area or method of image processing. Don't rush to dive into our image processing carefully, but grasp it from a general process.  Don't worry, you will almost always use: 

- The core part, because the basic building blocks of the library are defined here 
- The imgcodecs module, which provides functions for reading and writing 
- The highgui module, because it contains functions for displaying images in a window By declaring using namespace cv;, 

​	below, you can access library functions without explicitly stating the namespace. **But my advice is, don't do this in header files! **

```
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
```

​	The author slightly modified the opencv sample code, please see:

```
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
```

 	Now, let's analyze the main code. The make_up_example_path function simply finds the image in our example source code. You can print the path test manually!  First, we read the image "image.jpg" from the OpenCV samples. To do this, call the cv::imread function to load the image using the file path specified by the first argument. The second argument is optional and specifies the image format we want. This can be: 

- IMREAD_COLOR loads the image in BGR 8-bit format. This is the default used here. 
-  IMREAD_UNCHANGED loads the image as is (including alpha channel, if present) 
- IMREAD_GRAYSCALE loads the image as intensity image  

​	After reading, the image data is stored in a cv::Mat object. OpenCV supports image formats such as Windows bitmaps (bmp), portable image formats (pbm, pgm, ppm) and Sun raster (sr, ras). With the help of plugins (you need to specify them if you build the library yourself, although they are present in the package we provide by default), you can also load image formats such as JPEG (jpeg, jpg, jpe), JPEG 2000 (jp2 - codenamed Jasper in CMake), TIFF files (tiff, tif) and portable network graphics (png). OpenEXR is also a possibility.  Afterwards, a check is performed to determine if the image has been loaded correctly.

```
    auto image_path = make_up_example_path();
    Mat  img        = imread(image_path, IMREAD_COLOR);

    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
```

 	The image is then displayed using a call to the cv::imshow function. The first argument is the title of the window, and the second is the cv::Mat object that will be displayed. Since we want the window to remain displayed until the user presses a key (otherwise the program would end quickly), we use the cv::waitKey function, whose only argument is the time in milliseconds to wait for user input. Zero means wait forever. The return value is the key that was pressed.

```
  	imshow("Display window", img);
    std::cout << "Press 's' to save the image" << std::endl;
    int k = waitKey(0);  // Wait for a keystroke in the window
```

 	Finally, if the key pressed was the "s" key, the image is written to the file. To do this, the cv::imwrite function is called, which takes the file path and the cv::Mat object as parameters. It's worth mentioning that we can check the return value to see if our save was successful.

```
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

```

​	Sample code is at: examples/beginners

