#include "ImageInfoWidget.h"
#include "ImageInfoTools.h"
#include "ui_ImageInfoWidget.h"

ImageInfoWidget::ImageInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ImageInfoWidget) {
    ui->setupUi(this);
}

void ImageInfoWidget::onSetImageInfo(const QString &image_path) {
    qInfo() << "On set the image path" << image_path;
    if (image_path == current_hold_image_path) {
        req_fresh = false;
        return;
    }
    req_fresh               = true;
    current_hold_image_path = image_path;
}

void ImageInfoWidget::processLoadReading() {
    if (!req_fresh) return;

    if (current_hold_image_path.isEmpty()) {
        qCritical() << "On set the image path is empty";
        return;
    }

    ui->label_image_name->setText(
        ImageInfoTools::imageName(current_hold_image_path));
    ui->label_path->setText(ImageInfoTools::imagePath(current_hold_image_path));
    ui->image_birth_dateTime->setDateTime(
        ImageInfoTools::imageDate(current_hold_image_path));
    ui->label_image_size->setText(
        ImageInfoTools::ImageSizeInfoTools::fetchSize(current_hold_image_path));
    ui->label_image_date_dpix->setText(
        QString("%1 dpix").arg(ImageInfoTools::imageDpi(
            current_hold_image_path, ImageInfoTools::DpiSelections::X)));
    ui->label_image_date_dpiy->setText(
        QString("%1 dpiy").arg(ImageInfoTools::imageDpi(
            current_hold_image_path, ImageInfoTools::DpiSelections::Y)));
}

ImageInfoWidget::~ImageInfoWidget() {
    delete ui;
}
