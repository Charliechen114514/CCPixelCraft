#include "ImageHolder.h"

namespace ProvideCase {

QList<QImage> on_provide_null_case() {
    QList<QImage> images;
    for (int i = 0; i < 3; i++) {
        images.append(QImage());
    }
    return images;
}

QList<QImage> on_provide_only_one_case(const QString& image) {
    QList<QImage> images;
    images.append(QImage());
    images.append(QImage(image));
    images.append(QImage());
    return images;
}

QList<QImage> on_provide_first_case(const QStringList& image_list) {
    QList<QImage> images;
    images.append(QImage());
    images.append(QImage(image_list[0]));
    images.append(QImage(image_list[1]));
    return images;
}

QList<QImage> on_provide_last_case(const QStringList& image_list) {
    QList<QImage> images;
    auto          last_index = image_list.size() - 1;
    images.append(QImage(image_list[last_index - 1]));
    images.append(QImage(image_list[last_index]));
    images.append(QImage());
    return images;
}

QList<QImage> on_provide_middle_case(const QStringList&       image_list,
                                     const ImageHolder::Index index) {
    QList<QImage> images;
    images.append(QImage(image_list[index - 1]));
    images.append(QImage(image_list[index]));
    images.append(QImage(image_list[index + 1]));
    return images;
}

}  // namespace ProvideCase

QList<QImage> ImageHolder::get_packaged_image(const Index index) const {
    if (image_list.empty()) return ProvideCase::on_provide_null_case();
    if (image_list.size() == 1)
        return ProvideCase::on_provide_only_one_case(image_list[0]);
    if (index == 0) return ProvideCase::on_provide_first_case(image_list);
    if (index == image_list.size() - 1)
        return ProvideCase::on_provide_last_case(image_list);

    return ProvideCase::on_provide_middle_case(image_list, index);
}
