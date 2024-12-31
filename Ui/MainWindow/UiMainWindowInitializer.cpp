#include "UiMainWindowInitializer.h"
#include "CCImageMainWindow.h"
#include "ImageInfoWidget/ImageInfoWidget.h"
#include "StatusBarInfoManager/StatusBarInfoManager.h"
#include "WindowHelper/windoweventhelper.h"
#include "ui_CCImageMainWindow.h"

UiMainWindowInitializer::UiMainWindowInitializer(QObject *parent)
    : QObject{parent} {
}

void UiMainWindowInitializer::initUiMainWindowConnections(
    CCImageMainWindow *window) {
    _connect_toolBar(window);
    _connect_functional(window);
    _init_style(window);
    _init_keyAndMouseEvent(window);
}

void UiMainWindowInitializer::_init_keyAndMouseEvent(
    CCImageMainWindow *window) {
    /* key event */
    _init_keyEvent(window);
    /* mouse event */
    _init_mouseEvent(window);
}

void UiMainWindowInitializer::_init_keyEvent(CCImageMainWindow *window) {
    window->windowEventHelper->registerKeyEvents(
        Qt::Key_Left, std::bind(&CCImageMainWindow::prev_image, window));
    window->windowEventHelper->registerKeyEvents(
        Qt::Key_Right, std::bind(&CCImageMainWindow::next_image, window));
}

void UiMainWindowInitializer::_init_mouseEvent(CCImageMainWindow *window) {
}

void UiMainWindowInitializer::_connect_functional(CCImageMainWindow *window) {
    connect(window->ui->label_display, &DisplayLabel::tellMousePositionString,
            window->statusBarInfoManager.get(),
            &StatusBarManager::postPermanentMessage);
    connect(window->ui->label_display, &DisplayLabel::tellAddImages, window,
            &CCImageMainWindow::addImages);
    connect(window->ui->label_prev, &PreviewLabel::tellClickMe, window,
            &CCImageMainWindow::handling_label_selection);
    connect(window->ui->label_next, &PreviewLabel::tellClickMe, window,
            &CCImageMainWindow::handling_label_selection);
}

void UiMainWindowInitializer::_connect_toolBar(CCImageMainWindow *window) {
    /* toolbar connections */
    connect(window->ui->action_add_images, &QAction::triggered, window,
            &CCImageMainWindow::addImages);
    connect(window->ui->action_loadfromDir, &QAction::triggered, window,
            &CCImageMainWindow::loadFromDirent);
    connect(window->ui->action_next_image, &QAction::triggered, window,
            &CCImageMainWindow::next_image);
    connect(window->ui->action_prev_image, &QAction::triggered, window,
            &CCImageMainWindow::prev_image);
}

void UiMainWindowInitializer::_init_style(CCImageMainWindow *window) {
    QVBoxLayout *layout = new QVBoxLayout(window->ui->operating_widget);
    layout->addWidget(window->infoWidget.get());
    window->ui->operating_widget->setLayout(layout);
    window->infoWidget->hide();
}
