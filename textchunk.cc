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

    m_text.remove(m_currentPos - 1, 1);
    m_currentPos--;
    return true;
}

void
TextChunk::draw(QPainter& gc, QPointF topLeft, bool drawCursor)
{
    gc.drawGlyphRun(topLeft, m_glyphRun);
    if (!drawCursor) {
        return;
    }
    qreal descent = m_glyphRun.rawFont().descent();
    gc.fillRect(QRect(topLeft.toPoint() + QPoint(m_cursorOffset, -fontSize()), QSize(1, fontSize() + descent)),
                Qt::black);
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
    if (m_currentPos == m_text.size()) {
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
    auto tup     = m_layoutEngine.calculate(*this);
    m_glyphs     = std::get<0>(tup);
    m_glyphCount = std::get<1>(tup);

    QVector<quint32> glyphIndexes(static_cast<int>(m_glyphCount));
    QVector<QPointF> glyphPositions(static_cast<int>(m_glyphCount));

    qreal x = 0.0, y = 0.0;
    for (int i = 0; i < static_cast<int>(m_glyphCount); i++) {
        glyphIndexes[i]   = m_glyphs[i].index;
        glyphPositions[i] = QPointF(x + m_glyphs[i].x_offset, y - m_glyphs[i].y_offset) / 64;
        x += m_glyphs[i].x_advance;
        y -= m_glyphs[i].y_advance;

        if (i == m_currentPos - 1) {
            m_cursorOffset = x / 64;
        }
    }

    m_glyphRun       = QGlyphRun();
    QRawFont rawFont = QRawFont(font(), fontSize());
    m_glyphRun.setRawFont(rawFont);
    m_glyphRun.setGlyphIndexes(glyphIndexes);
    m_glyphRun.setPositions(glyphPositions);
}

qreal
TextChunk::cursorOffset()
{
    calculatePositions();
    return m_cursorOffset;
}

void
TextChunk::setCursorOffset(qreal offset)
{
    m_cursorOffset = 0.0;

    if (offset >= m_glyphRun.boundingRect().width()) {
        m_currentPos = m_text.size();
        return;
    }

    for (int i = 0; i < m_glyphCount; i++) {
        if ((m_cursorOffset + (m_glyphs[i].x_advance / 64)) > offset) {
            m_currentPos = i;
            break;
        }
        m_cursorOffset += (m_glyphs[i].x_advance / 64);
    }
    calculatePositions();
}
