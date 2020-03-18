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
}

void
PaintWidget::paintEvent(QPaintEvent* event)
{
    QPainter gc(this);
    gc.fillRect(event->rect(), Qt::white);

    gc.setPen(Qt::black);
    gc.drawRect(m_boundingRect);

    gc.translate(QPointF(m_margin.top(), m_margin.left()));

    if (m_boundingRectDone) {
        for (Layout& l : m_layouts) {
            l.draw(gc, m_boundingRect.topLeft(), m_boundingRect);
        }

        Layout& l = m_layouts.last();

        if (drawIBar) {
            QPoint cursorPos = l.cursor().toPoint();
            gc.fillRect(QRect(cursorPos, QSize(1, l.fontSize())), Qt::black);
        }
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

    if (m_layouts.isEmpty()) {
        Layout l;
        l.addChar(event->text());
        m_layouts.push_back(l);
    } else {
        Layout& l = m_layouts.last();
        l.addChar(event->text());
    }
    update();
}

void
PaintWidget::setFont(QString font)
{
    if (m_layouts.isEmpty()) {
        Layout l;
        l.setFont(font);
        m_layouts.push_back(l);
    } else {
        Layout& l = m_layouts.last();
        l.setFont(font);
    }

    update();
}

void
PaintWidget::setFontSize(unsigned size)
{
    if (m_layouts.isEmpty()) {
        Layout l;
        l.setFontSize(size);
        m_layouts.push_back(l);
        return;
    } else {
        Layout& l = m_layouts.last();
        l.setFontSize(size);
    }

    update();
}

void
PaintWidget::flipIBarStatus()
{
    drawIBar = !drawIBar;
    update();
}
