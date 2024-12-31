#include "PreviewLabel.h"

namespace {
static constexpr const char* enterQss =
    "QLabel { border: 3px solid rgba(0, 0, 255, 0.5); }";
static constexpr const char* leaveQss = "";
}  // namespace

PreviewLabel::PreviewLabel(QWidget* parent) : QLabel(parent) {
    setScaledContents(true);
}

void PreviewLabel::enterEvent(QEnterEvent* event) {
    if (pixmap().isNull()) return;
    setStyleSheet(enterQss);
}

void PreviewLabel::leaveEvent(QEvent* event) {
    if (pixmap().isNull()) return;
    setStyleSheet(leaveQss);
}

void PreviewLabel::mousePressEvent(QMouseEvent* event) {
    if (pixmap().isNull()) return;
    emit tellClickMe(this);
}
