#ifndef LAYOUT_HH
#define LAYOUT_HH

#include "textline.hh"
#include <QFont>
#include <QPainter>

struct TextLayout {
    TextLayout();
    void draw(QPainter& gc, const QPointF& pos, const QRect& clipRect);
    void addChar(const QString& _char);
    void deleteChar();

    void setFontSize(unsigned size);
    void setFont(QString font);
    void setMargins(QMargins margins);

    QPointF cursorPos();
    bool cursorToRight();
    bool cursorToLeft();
    bool cursorToUp();
    bool cursorToDown();

    private:
    QPointF m_cursorPos;
    unsigned m_currentLine = 0;
    QVector<TextLine> m_lines;
    QMargins m_margin = { 0, 0, 0, 0 };
};

#endif // LAYOUT_HH
