#ifndef LAYOUT_HH
#define LAYOUT_HH

#include <QFont>
#include <QPainter>
#include <raqm.h>

struct Cursor {
    int line = 0, pos = 0;
    operator QString() const { return QString("Line: %1 Pos: %2").arg(line).arg(pos); }
};

struct Layout {
    friend class LayoutEngine;

    void draw(QPainter& gc, const QPointF& pos, const QRect& clipRect);
    void addChar(const QString& _char);
    void deleteChar();

    void setFontSize(unsigned size);
    void setFont(QString font);

    unsigned fontSize();

    QPointF cursorPos();
    bool cursorToRight();
    bool cursorToLeft();
    bool cursorToUp();
    bool cursorToDown();

    private:
    unsigned m_fontSize;
    QString m_font;
    QVector<QString> m_text;
    raqm_direction_t m_direction = RAQM_DIRECTION_LTR;
    const char* m_language       = "en";
    QPointF m_cursorPos;
    Cursor m_cursor;
};

#endif // LAYOUT_HH
