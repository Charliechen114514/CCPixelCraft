#ifndef CCIMAGEMAINWINDOW_H
#define CCIMAGEMAINWINDOW_H
#include "ImageHolder/ImageHolder.h"
#include <QMainWindow>

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

private slots:
    void on_action_add_images_triggered();

    void on_action_loadfromDir_triggered();

private:
    Ui::CCImageMainWindow *ui;
    ImageHolder            holder;
    void                   initConnections();
};
#endif  // CCIMAGEMAINWINDOW_H
