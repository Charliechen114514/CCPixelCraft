#ifndef CCIMAGEMAINWINDOW_H
#define CCIMAGEMAINWINDOW_H
#include "ImageHolder/ImageHolder.h"
#include <QMainWindow>

class SizeManager;
class StatusBarManager;
class PreviewLabel;
class WindowEventHelper;
class ImageInfoWidget;
class OperateWidgetManage;

QT_BEGIN_NAMESPACE
namespace Ui {
class CCImageMainWindow;
}
QT_END_NAMESPACE

class CCImageMainWindow : public QMainWindow {
    Q_OBJECT

public:
    CCImageMainWindow(QWidget *parent = nullptr);
    ~CCImageMainWindow();
    void onSetCurrentImage(const ImageHolder::Index &index);

public slots:
    void addImages();
    void loadFromDirent();
    void next_image();
    void prev_image();
    void onCheckImageCurrentInfo();
    void onCheckImageInfo(const ImageHolder::Index &index);
    void handling_label_selection(PreviewLabel *label);
    void keyPressEvent(QKeyEvent *event) override;

private:
    friend class UiMainWindowInitializer;
    Ui::CCImageMainWindow               *ui;
    ImageHolder                          holder;
    std::shared_ptr<StatusBarManager>    statusBarInfoManager;
    std::shared_ptr<WindowEventHelper>   windowEventHelper;
    std::shared_ptr<ImageInfoWidget>     infoWidget{nullptr};
    std::shared_ptr<OperateWidgetManage> operateWidgetManage;
    void                                 initMemory();
    void                                 initConnections();
    void onSwitchTargetImageInfo(const QString &image_path);
    void onOpenTargetImageInfo(const QString &image_path);
    void adjustUiAccordingToGivenListImage(const QList<QImage> &images);
    void adjustOperateWidgetAccordingToGivenListImage();
};
#endif  // CCIMAGEMAINWINDOW_H
