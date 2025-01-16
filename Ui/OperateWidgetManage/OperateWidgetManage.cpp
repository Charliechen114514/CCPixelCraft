#include "OperateWidgetManage.h"
#include "SizeManager/SizeManager.h"
#include <QMainWindow>

OperateWidgetManage::OperateWidgetManage(QMainWindow* main_window) {
    this->main_window = main_window;
    sizeManager       = std::make_shared<SizeManager>();
    sizeManager->pushManage(main_window);
}

void OperateWidgetManage::showSubWidget(QWidget* widget) {
    sizeManager->pushSize(main_window, main_window->size());
    widget->show();
    if (widget->parentWidget()) widget->parentWidget()->show();
}

void OperateWidgetManage::hideSubWidget(QWidget* widget) {
    widget->hide();
    if (widget->parentWidget()) {
        widget->parentWidget()->hide();
    }
    sizeManager->resumeSize(main_window);
}
