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
TextLine::draw(QPainter& gc, QPointF topLeft, bool lineDrawCursor)
{
    int i                = 0;
    bool chunkDrawCursor = false;
    for (TextChunk& chunk : m_textChunks) {
        if (lineDrawCursor && i == m_currentChunk) {
            chunkDrawCursor = true;
        }
        chunk.draw(gc, topLeft + QPointF(0, m_boundingRect.height()), chunkDrawCursor);
        chunkDrawCursor = false;
        i++;
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

qreal
TextLine::cursorOffset()
{
    qreal offset = m_textChunks[m_currentChunk].cursorOffset();
    for (int i = 0; i < m_currentChunk; i++) {
        offset += m_textChunks[i].boundingRect().width();
    }
    return offset;
}

void
TextLine::setCursorOffset(qreal offset)
{
    for (int i = 0; i < m_textChunks.size(); i++) {
        if (m_textChunks[i].boundingRect().width() > offset) {
            m_currentChunk = i;
            m_textChunks[i].setCursorOffset(offset);
            break;
        }
        offset -= m_textChunks[i].boundingRect().width();
    }
}
