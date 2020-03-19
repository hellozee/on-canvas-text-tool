#ifndef PAINTWIDGET_HH
#define PAINTWIDGET_HH

#include "textlayout.hh"
#include <QTimer>
#include <QWidget>

class PaintWidget : public QWidget {
    Q_OBJECT
    public:
    explicit PaintWidget(QWidget* parent = nullptr);

    void setFont(QString font);
    void setFontSize(unsigned size);

    protected:
    void paintEvent(QPaintEvent* event);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void flipIBarStatus();

    private:
    QRect m_boundingRect;
    bool m_boundingRectDone = false, drawIBar = false;
    TextLayout m_layout;
    QTimer m_timer;
};

#endif // PAINTWIDGET_HH
