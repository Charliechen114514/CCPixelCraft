#ifndef PREVIEWLABEL_H
#define PREVIEWLABEL_H

#include <QLabel>

class PreviewLabel : public QLabel {
    Q_OBJECT
public:
    explicit PreviewLabel(QWidget* parent = nullptr);
    /* when press, set to the target label's path */
    virtual void mousePressEvent(QMouseEvent* event) override;

protected:
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;

signals:
    void tellClickMe(PreviewLabel* labelWho);
};

#endif  // PREVIEWLABEL_H
