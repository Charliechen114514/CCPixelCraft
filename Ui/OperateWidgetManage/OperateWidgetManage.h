#ifndef OPERATEWIDGETMANAGE_H
#define OPERATEWIDGETMANAGE_H
#include <QList>
class QMainWindow;
class QWidget;
class SizeManager;

class OperateWidgetManage {
public:
    OperateWidgetManage() = delete;
    OperateWidgetManage(QMainWindow* main_window);
    OperateWidgetManage(const OperateWidgetManage&)            = delete;
    OperateWidgetManage& operator=(const OperateWidgetManage&) = delete;

    void showSubWidget(QWidget* widget);
    void hideSubWidget(QWidget* widget);

private:
    QMainWindow*                 main_window{nullptr};
    std::shared_ptr<SizeManager> sizeManager;
};

#endif  // OPERATEWIDGETMANAGE_H
