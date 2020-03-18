#include "paintwidget.hh"

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

PaintWidget::PaintWidget(QWidget* parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void
PaintWidget::paintEvent(QPaintEvent* event)
{
    QPainter gc(this);
    gc.fillRect(event->rect(), Qt::white);

    gc.setPen(Qt::black);
    gc.drawRect(m_boundingRect);

    if (m_boundingRectDone) {
        //        int size = m_layoutEngine.fontSize();
        //        gc.fillRect(QRect(m_boundingRect.topLeft() + QPoint(m_margin.top(), m_margin.left()), QSize(2, size)),
        //                    Qt::black);
        for (Layout& l : m_layouts) {
            l.draw(gc, m_boundingRect.topLeft(), m_boundingRect);
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
        update();
        return;
    }

    Layout& l = m_layouts.last();
    l.addChar(event->text());
    update();
}

void
PaintWidget::setFont(QString font)
{
    qDebug() << m_lay;
    if (m_layouts.isEmpty()) {
        qDebug() << 2;
        Layout l;
        l.setFont(font);
        m_layouts.push_back(l);
        return;
    }

    Layout& l = m_layouts.last();
    l.setFont(font);
}

void
PaintWidget::setFontSize(unsigned size)
{
    if (m_layouts.isEmpty()) {
        Layout l;
        l.setFontSize(size);
        m_layouts.push_back(l);
        return;
    }

    Layout& l = m_layouts.last();
    l.setFontSize(size);
}
