#include "DisplayLabel.h"
#include <QMouseEvent>
namespace {

QString make_up_from_point(const QPoint& p) {
    return QString("X: %1, Y: %2").arg(p.x()).arg(p.y());
}

QString make_up_from_point_to_rgb(const QPixmap& map, const QPoint& p) {
    QRgb rgb = map.toImage().pixel(p);
    return QString(
               "<font color = red>R: %1</font>, "
               "<font color = green>G: %2</font>, "
               "<font color = blue>B: %3</font>")
        .arg(qRed(rgb))
        .arg(qGreen(rgb))
        .arg(qBlue(rgb));
}

QString gain_display(const QPixmap& map, const QPoint& p) {
    return make_up_from_point(p) + ", " + make_up_from_point_to_rgb(map, p);
}

};  // namespace

DisplayLabel::DisplayLabel(QWidget* parent) : QLabel(parent) {
    setStyleSheet("QLabel { border: 4px solid rgba(0, 0, 0, 0.7); }");
}

void DisplayLabel::mouseMoveEvent(QMouseEvent* event) {
    QLabel::mouseMoveEvent(event);

    if (pixmap().isNull()) {
        return;
    }
    emit tellMousePosition(event->pos());
    emit tellMousePositionString(gain_display(pixmap(), event->pos()));
}

void DisplayLabel::mouseDoubleClickEvent(QMouseEvent* event) {
    if (!pixmap().isNull()) {
        return;
    }

    emit tellAddImages();
}
