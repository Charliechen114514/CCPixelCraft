#include "StatusBarInfoManager.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include <stdexcept>
StatusBarManager::StatusBarManager(QStatusBar* bar, QObject* parent)
    : QObject(parent), permenent_label{new QLabel(bar)}, holding_bar{bar} {
    if (!bar) {
        throw std::invalid_argument(
            "StatusBarInfoManager::StatusBarInfoManager::bar is nullptr");
    }

    /* initialize as the label binding to the obj tree */
    bar->addPermanentWidget(permenent_label);
}

void StatusBarManager::postMessage(const QString& message, bool eternal) {
    if (eternal) {
        permenent_label->setText(message);
    } else {
        holding_bar->showMessage(message);
    }
}
