#include "layout.hh"
#include "layoutengine.hh"
#include <QDebug>

void
Layout::draw(QPainter& gc, const QPointF& pos, const QRect& clipRect)
{
    LayoutEngine engine;
    auto glyphRun = engine.calculate(*this);
    auto font     = glyphRun.rawFont();
    if (!glyphRun.isEmpty()) {
        gc.drawGlyphRun(pos + QPoint(0, font.ascent()), glyphRun);
    }
}

void
Layout::addChar(const QString& _char)
{
    m_text += _char;
}

void
Layout::deleteChar()
{
    m_text.remove(m_text.size() - 1, 1);
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
