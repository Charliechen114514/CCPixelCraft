#ifndef IMAGE_CONVERTOR_H
#define IMAGE_CONVERTOR_H

class Mat;
class QImage;

namespace Image_convertor {

Mat    convert(const QImage& image);
QImage convert(const Mat& mat);

};  // namespace Image_convertor

#endif  // IMAGE_CONVERTOR_H
