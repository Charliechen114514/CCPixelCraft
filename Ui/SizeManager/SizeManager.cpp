#include "SizeManager.h"
#include <QWidget>

void SizeManager::pushManage(QWidget* widget) {
    SizeInfo info{widget->minimumSize(), widget->maximumSize(),
                  widget->sizeHint()};
    infos.insert(widget, info);
}

void SizeManager::pushSize(QWidget* widget, QSize size) {
    auto it = infos.find(widget);
    if (it == infos.end()) return;
    it->lastSize = size;
    qDebug() << it->lastSize;
}

bool SizeManager::resumeSize(QWidget* widget) {
    auto it = infos.find(widget);
    if (it == infos.end()) return false;
    qDebug() << it->lastSize;
    widget->setFixedSize(it->lastSize);
    widget->setMinimumSize(it->minSize);
    widget->setMaximumSize(it->maxSize);
    return true;
}

void SizeManager::removeManage(QWidget* widget) {
    infos.remove(widget);
}
