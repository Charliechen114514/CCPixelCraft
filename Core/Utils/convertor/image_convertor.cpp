#include "image_convertor.h"
#include <QDebug>
#include <QImage>
#include <opencv2/opencv.hpp>
using namespace Image_convertor;

/*
    QImage和cv::Mat之间的转换
    需要注意的是：Image转Mat中一些操作是不被支持的！
*/

cv::Mat convert(const QImage& image) {
    cv::Mat mat;
    switch (image.format()) {
        case QImage::Format_Grayscale8:  // 灰度图，每个像素点1个字节（8位）
            // Mat构造：行数，列数，存储结构，数据，step每行多少字节
            mat = cv::Mat(image.height(), image.width(), CV_8UC1,
                          (void*)image.constBits(), image.bytesPerLine());
            break;
        case QImage::
            Format_ARGB32:  // uint32存储0xAARRGGBB，pc一般小端存储低位在前，所以字节顺序就成了BGRA
        case QImage::Format_RGB32:  // Alpha为FF
        case QImage::Format_ARGB32_Premultiplied:
            mat = cv::Mat(image.height(), image.width(), CV_8UC4,
                          (void*)image.constBits(), image.bytesPerLine());
            break;
        case QImage::Format_RGB888:  // RR,GG,BB字节顺序存储
            mat = cv::Mat(image.height(), image.width(), CV_8UC3,
                          (void*)image.constBits(), image.bytesPerLine());
            // opencv需要转为BGR的字节顺序
            cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
            break;
        case QImage::
            Format_RGBA64:  // uint64存储，顺序和Format_ARGB32相反，RGBA
            mat = cv::Mat(image.height(), image.width(), CV_16UC4,
                          (void*)image.constBits(), image.bytesPerLine());
            // opencv需要转为BGRA的字节顺序
            cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGRA);
            break;
        default:
            qDebug() << "Image_convertor::convert: unsupported image format";
            break;
    }
    return mat;
}

QImage convert(const cv::Mat& mat) {
    QImage image;
    switch (mat.type()) {
        case CV_8UC1:
            // QImage构造：数据，宽度，高度，每行多少字节，存储结构
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows,
                           mat.step, QImage::Format_Grayscale8);
            break;
        case CV_8UC3:
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows,
                           mat.step, QImage::Format_RGB888);
            image = image.rgbSwapped();  // BRG转为RGB
            // Qt5.14增加了Format_BGR888
            // image = QImage((const unsigned char*)mat.data, mat.cols,
            // mat.rows, mat.cols * 3, QImage::Format_BGR888);
            break;
        case CV_8UC4:
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows,
                           mat.step, QImage::Format_ARGB32);
            break;
        case CV_16UC4:
            image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows,
                           mat.step, QImage::Format_RGBA64);
            image = image.rgbSwapped();  // BRG转为RGB
            break;
    }
    return image;
}
