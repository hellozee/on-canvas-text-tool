#include "textline.hh"
#include <QDebug>

TextLine::TextLine()
{
    m_textChunks.push_back(TextChunk());
}

QRect
TextLine::boundingRect()
{
    return m_boundingRect;
}

void
TextLine::draw(QPainter& gc, QPointF topLeft)
{
    for (TextChunk& chunk : m_textChunks) {
        chunk.draw(gc, topLeft + QPointF(0, m_boundingRect.height()));
    }
}

void
TextLine::addChar(QString _char)
{
    m_textChunks[m_currentChunk].addChar(_char);
}

bool
TextLine::deleteChar()
{
    while (!m_textChunks[m_currentChunk].deleteChar()) {
        if (m_currentChunk == 0) {
            return false;
        }
        m_currentChunk--;
    }

    return true;
}

QVector<TextChunk>
TextLine::chunks()
{
    return m_textChunks;
}

QVector<QString>
TextLine::words()
{
}

unsigned
TextLine::currentChunkPos()
{
    return m_currentChunk;
}

bool
TextLine::cursorToLeft()
{
    if (m_textChunks[m_currentChunk].cursorToLeft()) {
        return true;
    }

    if (m_currentChunk == 0) {
        return false;
    }

    m_currentChunk--;
}

bool
TextLine::cursorToRight()
{
    if (m_textChunks[m_currentChunk].cursorToRight()) {
        return true;
    }

    if (m_currentChunk == m_textChunks.size() - 1) {
        return false;
    }

    m_currentChunk++;
}

void
TextLine::setFont(QString font)
{
    m_textChunks[m_currentChunk].setFont(font);
}

void
TextLine::setFontSize(unsigned size)
{
    m_textChunks[m_currentChunk].setFontSize(size);
}

TextLine
TextLine::newLine()
{
    TextLine line;
    TextChunk chunk = m_textChunks[m_currentChunk];
    line.setFont(chunk.font());
    line.setFontSize(chunk.fontSize());
    return line;
}

void
TextLine::calculateChunks()
{
    unsigned maxheight = 0, width = 0;
    for (TextChunk& chunk : m_textChunks) {
        chunk.calculatePositions();
        if (maxheight < chunk.fontSize()) {
            maxheight = chunk.fontSize();
        }
        width += chunk.boundingRect().width();
    }

    m_boundingRect.setSize(QSize(width, maxheight));
}
