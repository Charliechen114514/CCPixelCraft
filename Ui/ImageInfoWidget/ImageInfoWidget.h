#ifndef IMAGEINFOWIDGET_H
#define IMAGEINFOWIDGET_H

#include <QWidget>

namespace Ui {
class ImageInfoWidget;
}

class ImageInfoWidget : public QWidget {
    Q_OBJECT

public:
    explicit ImageInfoWidget(QWidget *parent = nullptr);
    void onSetImageInfo(const QString &image_path);
    void processLoadReading();
    ~ImageInfoWidget();

private:
    bool                 req_fresh{true};
    Ui::ImageInfoWidget *ui;
    QString              current_hold_image_path;
};

#endif  // IMAGEINFOWIDGET_H
