#ifndef PAINTWIDGET_HH
#define PAINTWIDGET_HH

#include "layout.hh"
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

    private:
    QRect m_boundingRect;
    bool m_boundingRectDone = false;
    QMargins m_margin{ 5, 5, 5, 5 };
    QVector<Layout> m_layouts;
};

#endif // PAINTWIDGET_HH
