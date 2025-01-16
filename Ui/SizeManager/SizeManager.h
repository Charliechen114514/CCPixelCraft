#ifndef SIZEMANAGER_H
#define SIZEMANAGER_H
#include <QMap>
#include <QSize>

class QWidget;

struct SizeInfo {
    QSize minSize;
    QSize maxSize;
    QSize lastSize;
};

class SizeManager {
public:
    SizeManager() = default;
    void pushManage(QWidget* widget);
    bool inline isInManage(QWidget* widget) {
        return infos.contains(widget);
    }
    void pushSize(QWidget* widget, QSize size);
    bool resumeSize(QWidget* widget);
    void removeManage(QWidget* widget);

private:
    QMap<QWidget*, SizeInfo> infos;
};

#endif  // SIZEMANAGER_H
