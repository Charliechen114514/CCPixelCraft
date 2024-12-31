#ifndef DISPLAYLABEL_H
#define DISPLAYLABEL_H

#include <QLabel>

class DisplayLabel : public QLabel {
    Q_OBJECT
public:
    explicit DisplayLabel(QWidget* parent = nullptr);

    /*  override the mouseMoveEvent for the
     *  latter to emit a signal with the
     */

    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
signals:
    void tellMousePosition(QPoint point);
    void tellMousePositionString(QString message);
    void tellAddImages();
};

#endif  // DISPLAYLABEL_H
