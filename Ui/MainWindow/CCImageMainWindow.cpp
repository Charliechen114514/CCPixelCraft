#include "CCImageMainWindow.h"
#include "ImageImporter.h"
#include "ImageInfoWidget/ImageInfoWidget.h"
#include "OperateWidgetManage/OperateWidgetManage.h"
#include "SizeManager/SizeManager.h"
#include "StatusBarInfoManager/StatusBarInfoManager.h"
#include "UiMainWindowInitializer.h"
#include "UiUtils.h"
#include "WindowHelper/windoweventhelper.h"
#include "ui_CCImageMainWindow.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

/*
    1. init Memory each components requried
*/

CCImageMainWindow::CCImageMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CCImageMainWindow) {
    ui->setupUi(this);
    initMemory();
    initConnections();
}

void CCImageMainWindow::initMemory() {
    this->statusBarInfoManager =
        std::make_shared<StatusBarManager>(ui->statusbar, this);
    this->windowEventHelper   = std::make_shared<WindowEventHelper>();
    this->operateWidgetManage = std::make_shared<OperateWidgetManage>(this);
}

void CCImageMainWindow::initConnections() {
    UiMainWindowInitializer::initUiMainWindowConnections(this);
}

void CCImageMainWindow::onSwitchTargetImageInfo(const QString &image_path) {
    if (!infoWidget) {
        this->infoWidget =
            std::make_shared<ImageInfoWidget>(ui->operating_widget);
        ui->operating_widget->layout()->addWidget(this->infoWidget.get());
    }

    if (!this->infoWidget->isVisible()) {
        infoWidget->onSetImageInfo(image_path);
        infoWidget->processLoadReading();
        operateWidgetManage->showSubWidget(infoWidget.get());
        ui->action_browse_image_info->setText("关闭图像信息");
    } else {
        operateWidgetManage->hideSubWidget(infoWidget.get());
        ui->action_browse_image_info->setText("浏览图像信息");
    }
}

void CCImageMainWindow::onOpenTargetImageInfo(const QString &image_path) {
    if (!infoWidget) return;

    if (this->infoWidget->isVisible()) {
        infoWidget->onSetImageInfo(image_path);
        infoWidget->processLoadReading();
    }
}

void CCImageMainWindow::adjustUiAccordingToGivenListImage(
    const QList<QImage> &images) {
    ui->action_prev_image->setEnabled(
        !images.at(ImageHolder::ImageHolderIndex::PREV_PAGE).isNull());

    ui->action_next_image->setEnabled(
        !images.at(ImageHolder::ImageHolderIndex::NEXT_PAGE).isNull());

    ui->action_browse_image_info->setEnabled(
        !images.at(ImageHolder::ImageHolderIndex::CURRENT_PAGE).isNull());

    /* process the loading widget */
    adjustOperateWidgetAccordingToGivenListImage();
}

void CCImageMainWindow::adjustOperateWidgetAccordingToGivenListImage() {
    onOpenTargetImageInfo(holder.get_index_path(holder.get_current_index()));
}

void CCImageMainWindow::onSetCurrentImage(const ImageHolder::Index &index) {
    QList<QImage> images = holder.get_packaged_image(index);
    /* adjust ui interface */
    adjustUiAccordingToGivenListImage(images);
    try {
        QPixmap current =
            QPixmap::fromImage(
                images.at(ImageHolder::ImageHolderIndex::CURRENT_PAGE))
                .scaled(ui->label_display->size());
        ui->label_display->setPixmap(current);
        ui->label_current->setPixmap(current.scaled(ui->label_current->size()));
        if (!images.at(ImageHolder::ImageHolderIndex::PREV_PAGE).isNull()) {
            ui->label_prev->setPixmap(
                QPixmap::fromImage(
                    images.at(ImageHolder::ImageHolderIndex::PREV_PAGE))
                    .scaled(ui->label_prev->size()));
        } else {
            ui->label_prev->setPixmap(QPixmap());
        }
        if (!images.at(ImageHolder::ImageHolderIndex::NEXT_PAGE).isNull()) {
            ui->label_next->setPixmap(
                QPixmap::fromImage(
                    images.at(ImageHolder::ImageHolderIndex::NEXT_PAGE))
                    .scaled(ui->label_next->size()));
        } else {
            ui->label_next->setPixmap(QPixmap());
        }

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

void CCImageMainWindow::addImages() {
    QStringList image_list = ImageImporter::import_from_dialog_default(
        UiUtils::provide_default_selection_dirent());
    if (image_list.empty()) return;
    holder.insertImages(image_list, holder.size());
    onSetCurrentImage(holder.get_current_index());
}

void CCImageMainWindow::loadFromDirent() {
    QString dir_path = QFileDialog::getExistingDirectory(
        this, "请选择图像文件夹", UiUtils::provide_default_selection_dirent());
    if (dir_path.isEmpty()) return;
    QStringList image_list =
        ImageImporter::import_from_dirent_default(dir_path);
    if (image_list.empty()) return;
    holder.insertImages(image_list, holder.size());
    onSetCurrentImage(holder.get_current_index());
}

void CCImageMainWindow::next_image() {
    if (holder.size() == 0) {
        statusBarInfoManager->postTemporaryMessage("请先选取图片加载浏览");
        return;
    }
    auto index = holder.switch_next_one();
    onSetCurrentImage(index);
}

void CCImageMainWindow::prev_image() {
    if (holder.size() == 0) {
        statusBarInfoManager->postTemporaryMessage("请先选取图片加载浏览");
        return;
    }
    auto index = holder.switch_prev_one();
    onSetCurrentImage(index);
}

void CCImageMainWindow::onCheckImageCurrentInfo() {
    auto index = holder.get_current_index();
    if (index == ImageHolder::INVALID_INDEX) {
        statusBarInfoManager->postTemporaryMessage("请先选取图片加载浏览");
        return;
    }
    onCheckImageInfo(index);
}

void CCImageMainWindow::onCheckImageInfo(const ImageHolder::Index &index) {
    QString image_path = holder.get_index_path(index);
    onSwitchTargetImageInfo(image_path);
}

void CCImageMainWindow::handling_label_selection(PreviewLabel *label) {
    if (label == ui->label_prev) {
        prev_image();
    } else if (label == ui->label_next) {
        next_image();
    }
}

void CCImageMainWindow::keyPressEvent(QKeyEvent *event) {
    windowEventHelper->setModifiers(event->modifiers(),
                                    WindowEventHelper::Monitor::Global);
    windowEventHelper->doKeyProcess(event->key());
}
