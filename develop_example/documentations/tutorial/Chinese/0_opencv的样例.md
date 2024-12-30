# 从0开始

​	大伙都知道，opencv是一个图像处理的一个重要的库。在 OpenCV 4 中，我们有多个模块。每个模块负责不同的图像处理领域或方法。先不着急仔细一头扎进我们的图像处理里去，而是从一个大概的流程进行把握。

​	别担心，您几乎总是会使用：

- 核心部分，因为这里定义了库的基本构建块

- imgcodecs 模块，它提供读取和写入的函数
- highgui 模块，因为它包含在窗口中显示图像的函数

通过声明 using namespace cv;，在下面，可以访问库函数而无需明确说明命名空间。**但是笔者的建议是，不要头文件中这样干！**

```
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
```

​	笔者稍微魔改了一下opencv的样例代码，请看：

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

​	现在，让我们分析一下主代码。make_up_example_path函数只是简单的找到了我们的example源码中的image图像。这一点您可以手动的打印一下路径测试！

​	首先，我们从 OpenCV 样本中读取图像"image.jpg”。为此，调用 cv::imread 函数使用第一个参数指定的文件路径加载图像。第二个参数是可选的，指定我们想要的图像格式。这可能是：

- IMREAD_COLOR 以 BGR 8 位格式加载图像。这是此处使用的默认值。

- IMREAD_UNCHANGED 按原样加载图像（包括 alpha 通道，如果存在）
- IMREAD_GRAYSCALE 将图像加载为强度图像

​	读取后，图像数据将存储在 cv::Mat 对象中。OpenCV 支持 Windows 位图 (bmp)、便携式图像格式 (pbm、pgm、ppm) 和 Sun 光栅 (sr、ras) 等图像格式。借助插件（如果您自行构建库，则需要指定使用它们，尽管我们默认提供的软件包中存在这些插件），您还可以加载图像格式，如 JPEG (jpeg、jpg、jpe)、JPEG 2000 (jp2 - 在 CMake 中代号为 Jasper)、TIFF 文件 (tiff、tif) 和便携式网络图形 (png)。此外，OpenEXR 也是一种可能性。

​	之后，将执行检查，以确定图像是否已正确加载。

```
    auto image_path = make_up_example_path();
    Mat  img        = imread(image_path, IMREAD_COLOR);

    if (img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
```

​	然后，使用对 cv::imshow 函数的调用显示图像。第一个参数是窗口的标题，第二个参数是将显示的 cv::Mat 对象。因为我们希望窗口一直显示，直到用户按下某个键（否则程序会很快结束），所以我们使用 cv::waitKey 函数，该函数的唯一参数就是等待用户输入的时间（以毫秒为单位）。零表示永远等待。返回值是按下的键。

```
  	imshow("Display window", img);
    std::cout << "Press 's' to save the image" << std::endl;
    int k = waitKey(0);  // Wait for a keystroke in the window
```

​	最后，如果按下的键是“s”键，则将图像写入文件。为此，将调用 cv::imwrite 函数，该函数以文件路径和 cv::Mat 对象作为参数。值得一提的是：我们可以检查返回值来查看我们的保存是否成功。

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

​	样例代码在:examples/beginners