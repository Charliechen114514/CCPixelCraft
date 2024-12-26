#include "CCImageMainWindow.h"
#include "ImageImporter.h"
#include "UiUtils.h"
#include "ui_CCImageMainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
CCImageMainWindow::CCImageMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CCImageMainWindow) {
    ui->setupUi(this);
    initConnections();
}

void CCImageMainWindow::initConnections() {
}

void CCImageMainWindow::onSetCurrentImage(const ImageHolder::Index &index) {
    QList<QImage> images = holder.get_packaged_image(index);
    try {
        ui->label_display->setPixmap(
            QPixmap::fromImage(
                images.at(ImageHolder::ImageHolderIndex::CURRENT_PAGE))
                .scaled(ui->label_display->size()));
        ui->label_prev->setPixmap(
            QPixmap::fromImage(
                images.at(ImageHolder::ImageHolderIndex::PREV_PAGE))
                .scaled(ui->label_prev->size()));
        ui->label_next->setPixmap(
            QPixmap::fromImage(
                images.at(ImageHolder::ImageHolderIndex::NEXT_PAGE))
                .scaled(ui->label_next->size()));
        ui->label_current->setPixmap(
            QPixmap::fromImage(
                images.at(ImageHolder::ImageHolderIndex::CURRENT_PAGE))
                .scaled(ui->label_current->size()));
    } catch (...) {
        QMessageBox::critical(this, "发生错误", "获取图像错误！");
    }
}
CCImageMainWindow::~CCImageMainWindow() {
    delete ui;
}

/*
    toolbar actions
*/
void CCImageMainWindow::on_action_add_images_triggered() {
    QStringList image_list = ImageImporter::import_from_dialog_default(
        UiUtils::provide_default_selection_dirent());
    if (image_list.empty()) return;
    holder.insertImages(image_list, holder.size());
    onSetCurrentImage(holder.get_current_index());
}

void CCImageMainWindow::on_action_loadfromDir_triggered() {
    QString dir_path = QFileDialog::getExistingDirectory(
        this, "请选择图像文件夹", UiUtils::provide_default_selection_dirent());
    if (dir_path.isEmpty()) return;
    QStringList image_list =
        ImageImporter::import_from_dirent_default(dir_path);
    if (image_list.empty()) return;
    holder.insertImages(image_list, holder.size());
    onSetCurrentImage(holder.get_current_index());
}
