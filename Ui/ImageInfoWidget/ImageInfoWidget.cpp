#include "ImageInfoWidget.h"
#include "ui_ImageInfoWidget.h"

ImageInfoWidget::ImageInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ImageInfoWidget) {
    ui->setupUi(this);
}

void ImageInfoWidget::onSetImageInfo(const QString &image_path) {
}

ImageInfoWidget::~ImageInfoWidget() {
    delete ui;
}
