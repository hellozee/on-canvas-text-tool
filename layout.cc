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
        if (m_cursor.line == i) {
            int horizontalOffset = 0;
            auto glyphPositions  = glyphRun.positions();
            for (int j = 0; j < glyphPositions.size(); j++) {
                if (m_cursor.pos == j + 1) {
                    horizontalOffset = glyphPositions[j].x() + font.averageCharWidth();
                    break;
                }
            }

            m_cursorPos = pos + QPoint(horizontalOffset + 1, lineheight + font.descent());
        }
        lineheight += font.ascent() + 1;
    }
}

void
Layout::addChar(const QString& _char)
{
    if (m_text.isEmpty()) {
        m_text.push_back(QString());
    }

    QString& str = m_text[m_cursor.line];
    if (_char == "\r") {
        if (m_cursor.pos == str.size()) {
            m_text.push_back(QString());
        } else {
            auto partOfString = str.right(str.size() - m_cursor.pos);
            str.resize(str.size() - m_cursor.pos);
            m_text.insert(m_cursor.line + 1, partOfString);
        }
        m_cursor.line++;
        m_cursor.pos = 0;
        return;
    }

    if (_char == "\b") {
        deleteChar();
        return;
    }

    str.insert(m_cursor.pos, _char);
    m_cursor.pos++;
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
Layout::cursorPos()
{
    return m_cursorPos;
}

unsigned
Layout::fontSize()
{
    return m_fontSize;
}

bool
Layout::cursorToRight()
{
    qDebug() << "R" << m_cursor;
    if (m_cursor.pos == m_text[m_cursor.line].size()) {
        return cursorToDown();
    }
    m_cursor.pos++;
    return true;
}

bool
Layout::cursorToLeft()
{
    qDebug() << "L" << m_cursor;
    if (m_cursor.pos == 0) {
        return cursorToUp();
    }
    m_cursor.pos--;
    return true;
}

bool
Layout::cursorToUp()
{
    qDebug() << "U" << m_cursor;
    if (m_cursor.line == 0) {
        return false;
    }

    m_cursor.line--;
    if (m_cursor.pos > m_text[m_cursor.line].size()) {
        m_cursor.pos = m_text[m_cursor.line].size();
    }
    return true;
}

bool
Layout::cursorToDown()
{
    if (m_cursor.line == m_text.size()) {
        return false;
    }

    m_cursor.line++;
    if (m_cursor.pos > m_text[m_cursor.line].size()) {
        m_cursor.pos = m_text[m_cursor.line].size();
    }
    qDebug() << "D" << m_cursor;
    return true;
}
