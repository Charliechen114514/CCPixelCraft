#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H
#include <QImage>
#include <QStringList>

class ImageHolder {
public:
    using Index = QStringList::size_type;
    struct ImageHolderIndex {
        static constexpr ImageHolder::Index PREV_PAGE    = 0;
        static constexpr ImageHolder::Index CURRENT_PAGE = 1;
        static constexpr ImageHolder::Index NEXT_PAGE    = 2;
    };
    static constexpr Index INVALID_INDEX       = -1;
    ImageHolder()                              = default;
    ~ImageHolder()                             = default;
    ImageHolder(const ImageHolder&)            = delete;
    ImageHolder& operator=(const ImageHolder&) = delete;

    // followings provide the basic functions of ImageHolder
    QImage        get_image(const Index index) const;
    QList<QImage> get_packaged_image(const Index index) const;
    QString       get_index_path(const Index index) const {
        if (index >= image_list.size()) {
            return QString();
        }
        return image_list[index];
    }

    Index size() const {
        return image_list.size();
    }
    Index get_current_index() const {
        return current_index;
    }

    void insertImage(const QString& path, const Index index) {
        image_list.insert(index, path);
        current_index = index;
    }
    void insertImages(const QStringList& paths, const Index index) {
        Index inner = index;
        for (const auto& each : paths) {
            image_list.insert(inner++, each);
        }
        current_index = --inner;
    }

    Index inline switch_prev_one() {
        current_index--;
        if (current_index < 0) {
            current_index = 0;
        }
        return current_index;
    }
    Index inline switch_next_one() {
        current_index++;
        if (current_index >= image_list.size()) {
            current_index = image_list.size() - 1;
        }
        return current_index;
    }

    void removeImage(const Index index);
    void removeImages(const Index begin, const Index end);
    void removeImages(const QList<Index>& indexes);

    void clear();

private:
    QStringList image_list{};
    Index       current_index{INVALID_INDEX};
};

#endif  // IMAGEHOLDER_H
