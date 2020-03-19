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
    int nextLine = m_margin.top();
    for (TextLine line : m_lines) {
        line.calculateChunks();
        line.draw(gc, pos + QPoint(m_margin.left(), nextLine));
        nextLine += line.boundingRect().height();
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

QPointF
TextLayout::cursorPos()
{
    return m_cursorPos;
}

bool
TextLayout::cursorToRight()
{
    return true;
}

bool
TextLayout::cursorToLeft()
{
    return true;
}

bool
TextLayout::cursorToUp()
{
    return true;
}

bool
TextLayout::cursorToDown()
{
    return true;
}

void
TextLayout::setMargins(QMargins margins)
{
    m_margin = margins;
}
