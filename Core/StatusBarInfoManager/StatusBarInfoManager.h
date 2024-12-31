#ifndef STATUSBARINFOMANAGER_H
#define STATUSBARINFOMANAGER_H
#include "predef.h"
#include <QObject>
#include <QString>
class QStatusBar;
class QLabel;

/*
    StatusBar Manager holds the management of the
    statusbar in Window
*/
class StatusBarManager : public QObject {
    Q_OBJECT
public:
    StatusBarManager(QStatusBar* bar, QObject* parent = nullptr);

    void postMessage(const QString& message, bool eternal = false);

public slots:
    void inline postPermanentMessage(const QString& message) {
        postMessage(message, true);
    }
    void inline postTemporaryMessage(const QString& message) {
        postMessage(message, false);
    }

private:
    BORROW_FROM_EXTERN QStatusBar* holding_bar{nullptr};
    USE_OBJTREE QLabel*            permenent_label{nullptr};
};

#endif  // STATUSBARINFOMANAGER_H
