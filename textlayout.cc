#include "textlayout.hh"
#include "layoutengine.hh"
#include <QDebug>

TextLayout::TextLayout()
{
    m_lines.push_back(TextLine());
}

void
TextLayout::draw(QPainter& gc, const QPointF& pos, const QRect& clipRect)
{
    gc.setClipRect(clipRect);
    int nextLine        = m_margin.top();
    int i               = 0;
    bool lineDrawCursor = false;
    for (TextLine line : m_lines) {

        if (m_drawCursor && i == m_currentLine) {
            lineDrawCursor = true;
        }

        line.calculateChunks();
        line.draw(gc, pos + QPoint(m_margin.left(), nextLine), lineDrawCursor);
        nextLine += line.boundingRect().height();
        lineDrawCursor = false;
        i++;
    }
}

void
TextLayout::addChar(const QString& _char)
{
    if (_char == "\r") {
        m_lines.push_back(m_lines[m_currentLine].newLine());
        m_currentLine++;
        return;
    }

    if (_char == "\b") {
        deleteChar();
        return;
    }

    m_lines[m_currentLine].addChar(_char);
}

void
TextLayout::deleteChar()
{
    while (!m_lines[m_currentLine].deleteChar()) {
        if (m_currentLine == 0) {
            break;
        }
        m_currentLine--;
    }
}

void
TextLayout::setFont(QString font)
{
    m_lines[m_currentLine].setFont(font);
}

void
TextLayout::setFontSize(unsigned size)
{
    m_lines[m_currentLine].setFontSize(size);
}

void
TextLayout::cursorToRight()
{
    if (!m_lines[m_currentLine].cursorToRight()) {
        cursorToDown();
    }
}

void
TextLayout::cursorToLeft()
{
    if (!m_lines[m_currentLine].cursorToLeft()) {
        cursorToUp();
    }
}

void
TextLayout::cursorToUp()
{
    if (m_currentLine != 0) {
        qreal offset = m_lines[m_currentLine].cursorOffset();
        m_currentLine--;
        m_lines[m_currentLine].setCursorOffset(offset);
    }
}

void
TextLayout::cursorToDown()
{
    if (m_currentLine < m_lines.size() - 1) {
        qreal offset = m_lines[m_currentLine].cursorOffset();
        m_currentLine++;
        m_lines[m_currentLine].setCursorOffset(offset);
    }
}

void
TextLayout::setMargins(QMargins margins)
{
    m_margin = margins;
}

void
TextLayout::drawCursor(bool draw)
{
    m_drawCursor = draw;
}

void
TextLayout::moveCursorTo(QPoint pos)
{
    int nextLine = m_margin.top();
    for (int i = 0; i < m_lines.size(); i++) {
        m_lines[i].calculateChunks();
        nextLine += m_lines[i].boundingRect().height();
        if (pos.y() < nextLine) {
            m_lines[i].setCursorOffset(pos.x());
            m_currentLine = i;
            break;
        }
    }
}
