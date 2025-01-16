#include "ImageInfoTools.h"
#include <QFileInfo>
#include <QImage>
#include <QPixmap>
#include <QString>

namespace ImageInfoTools {

namespace ImageSizeInfoTools {
static constexpr qreal KB = 1024.0;
static constexpr qreal MB = KB * KB;
static constexpr qreal GB = MB * KB;

QString fetchBitLength(const QImage &image) {
    return QString::number(image.depth()) + "位";
}

QString formatSize(qint64 size) {
    if (size < KB) {
        return QString::number(size) + " B";
    } else if (size < MB) {
        return QString::number(size / KB, 'f', 2) + " KB";
    } else if (size < GB) {
        return QString::number(size / MB, 'f', 2) + " MB";
    } else {
        return QString::number(size / GB, 'f', 2) + " GB";
    }
}

QString fetchImageSize(const QString &where) {
    return formatSize(QFileInfo(where).size());
}

QString fetchSize(const QString &where) {
    QImage image(where);
    QSize  s = image.size();
    return QString("%1x%2 %3 %4")
        .arg(s.width())
        .arg(s.height())
        .arg(fetchBitLength(image))
        .arg(fetchImageSize(where));
}

}  // namespace ImageSizeInfoTools

QString imageName(const QString &image_path) {
    return QFileInfo(image_path).baseName();
}

QString imagePath(const QString &image_path) {
    return image_path;
}

QDateTime imageDate(const QString &image_path) {
    return QFileInfo(image_path).birthTime();
}

QString imageDpi(const QString &image_info, const DpiSelections &s) {
    QPixmap m(image_info);

    switch (s) {
        case DpiSelections::X:
            return QString::number(m.physicalDpiX());
        case DpiSelections::Y:
            return QString::number(m.physicalDpiY());
        case DpiSelections::Both:
            return QString("%1 dpiX %2 dpiY")
                .arg(QString::number(m.physicalDpiX()))
                .arg(QString::number(m.physicalDpiY()));
    }
}

};  // namespace ImageInfoTools
