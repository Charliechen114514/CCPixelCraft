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
    ~ImageInfoWidget();

private:
    Ui::ImageInfoWidget *ui;
};

#endif  // IMAGEINFOWIDGET_H
