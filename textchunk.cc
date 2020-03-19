#include "textchunk.hh"
#include <QDebug>
void
TextChunk::addChar(QString _char)
{
    m_text.insert(m_currentPos, _char);
    m_currentPos++;
}

bool
TextChunk::deleteChar()
{
    if (m_text.isEmpty()) {
        return false;
    }

    m_text.remove(m_currentPos, 1);
    m_currentPos--;
    return true;
}

void
TextChunk::draw(QPainter& gc, QPointF topLeft)
{
    gc.drawGlyphRun(topLeft, m_glyphRun);
}

void
TextChunk::setFont(QString font)
{
    m_font = font;
}

void
TextChunk::setFontSize(unsigned size)
{
    m_fontSize = size;
}

QString
TextChunk::text()
{
    return m_text;
}

QString
TextChunk::font()
{
    return m_font;
}

unsigned
TextChunk::fontSize()
{
    return m_fontSize;
}

QRectF
TextChunk::boundingRect()
{
    return m_glyphRun.boundingRect();
}

bool
TextChunk::cursorToLeft()
{
    if (m_currentPos == 0) {
        return false;
    }

    m_currentPos--;
    return true;
}

bool
TextChunk::cursorToRight()
{
    if (m_currentPos == m_text.size() - 1) {
        return false;
    }

    m_currentPos++;
    return true;
}

raqm_direction_t
TextChunk::direction()
{
    return m_direction;
}

char*
TextChunk::language()
{
    return m_language;
}

void
TextChunk::calculatePositions()
{
    auto tup    = m_layoutEngine.calculate(*this);
    auto glyphs = std::get<0>(tup);
    auto count  = std::get<1>(tup);

    QVector<quint32> glyphIndexes(static_cast<int>(count));
    QVector<QPointF> glyphPositions(static_cast<int>(count));

    qreal x = 0.0, y = 0.0;
    for (int i = 0; i < static_cast<int>(count); i++) {
        glyphIndexes[i]   = glyphs[i].index;
        glyphPositions[i] = QPointF(x + glyphs[i].x_offset, y - glyphs[i].y_offset) / 64;
        x += glyphs[i].x_advance;
        y -= glyphs[i].y_advance;
    }

    m_glyphRun       = QGlyphRun();
    QRawFont rawFont = QRawFont(font(), fontSize());
    m_glyphRun.setRawFont(rawFont);
    m_glyphRun.setGlyphIndexes(glyphIndexes);
    m_glyphRun.setPositions(glyphPositions);
}
