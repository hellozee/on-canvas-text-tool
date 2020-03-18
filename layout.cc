#include "layout.hh"
#include "layoutengine.hh"
#include <QDebug>

void
Layout::draw(QPainter& gc, const QPointF& pos, const QRect& clipRect)
{
    qreal lineheight = 0;
    for (int i = 0; i < m_text.size(); i++) {
        LayoutEngine engine;
        auto glyphRun = engine.calculate(*this, m_text[i]);
        auto font     = glyphRun.rawFont();
        if (!glyphRun.isEmpty()) {
            gc.drawGlyphRun(pos + QPoint(0, font.ascent() + lineheight), glyphRun);
        }
        m_cursor = pos + QPoint(glyphRun.boundingRect().width() + 2, lineheight + font.descent());
        lineheight += font.ascent() + 1;
    }
}

void
Layout::addChar(const QString& _char)
{
    if (m_text.isEmpty()) {
        m_text.push_back(QString());
    }

    QString& str = m_text.last();
    if (_char == "\r") {
        m_text.push_back(QString());
        return;
    }

    if (_char == "\b") {
        deleteChar();
        return;
    }

    str += _char;
}

void
Layout::deleteChar()
{
    if (m_text.isEmpty()) {
        return;
    }
    QString& str = m_text.last();
    str.resize(str.size() - 1);
}

void
Layout::setFont(QString font)
{
    m_font = font;
}

void
Layout::setFontSize(unsigned size)
{
    m_fontSize = size;
}

QPointF
Layout::cursor()
{
    return m_cursor;
}

unsigned
Layout::fontSize()
{
    return m_fontSize;
}
