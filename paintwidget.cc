#include "paintwidget.hh"

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

PaintWidget::PaintWidget(QWidget* parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    m_timer.setInterval(500);
    connect(&m_timer, &QTimer::timeout, this, &PaintWidget::flipIBarStatus);
    m_timer.start();

    m_layout.setMargins(QMargins{ 5, 5, 5, 5 });
}

void
PaintWidget::paintEvent(QPaintEvent* event)
{
    QPainter gc(this);
    gc.fillRect(event->rect(), Qt::white);

    gc.setPen(Qt::black);
    gc.drawRect(m_boundingRect);

    if (m_boundingRectDone) {
        m_layout.draw(gc, m_boundingRect.topLeft(), m_boundingRect);
    }
}

void
PaintWidget::mousePressEvent(QMouseEvent* event)
{
    if (!m_boundingRectDone) {
        m_boundingRect.setTopLeft(event->pos());
        return;
    }
}

void
PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_boundingRectDone) {
        m_boundingRect.setBottomRight(event->pos());
        update();
        return;
    }
}

void
PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (!m_boundingRectDone) {
        m_boundingRect.setBottomRight(event->pos());
        update();
        m_boundingRectDone = true;
        return;
    }
}

void
PaintWidget::keyPressEvent(QKeyEvent* event)
{
    if (!m_boundingRectDone) {
        return;
    }

    switch (event->key()) {
        case Qt::Key_Left: {
            m_layout.cursorToLeft();
            update();
            return;
        }
        case Qt::Key_Right: {
            m_layout.cursorToRight();
            update();
            return;
        }
        case Qt::Key_Up: {
            m_layout.cursorToUp();
            update();
            return;
        }
        case Qt::Key_Down: {
            m_layout.cursorToDown();
            update();
            return;
        }
    }

    m_layout.addChar(event->text());
    update();
}

void
PaintWidget::setFont(QString font)
{
    m_layout.setFont(font);
    update();
}

void
PaintWidget::setFontSize(unsigned size)
{
    m_layout.setFontSize(size);
    update();
}

void
PaintWidget::flipIBarStatus()
{
    drawIBar = !drawIBar;
    update();
}
