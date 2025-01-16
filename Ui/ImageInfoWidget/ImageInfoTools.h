#ifndef IMAGEINFOTOOLS_H
#define IMAGEINFOTOOLS_H

class QString;
class QDateTime;
class QImage;

namespace ImageInfoTools {

namespace ImageSizeInfoTools {
QString fetchSize(const QString &where);
}  // namespace ImageSizeInfoTools

QString   imageName(const QString &image_path);
QString   imagePath(const QString &image_path);
QDateTime imageDate(const QString &image_path);

enum class DpiSelections { X, Y, Both };
QString imageDpi(const QString &image_info, const DpiSelections &s);

};  // namespace ImageInfoTools

#endif  // IMAGEINFOTOOLS_H
