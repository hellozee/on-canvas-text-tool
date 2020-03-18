#ifndef LAYOUT_HH
#define LAYOUT_HH

#include <QFont>
#include <QPainter>
#include <raqm.h>

struct Layout {
    friend class LayoutEngine;

    void draw(QPainter& gc, const QPointF& pos, const QRect& clipRect);
    void addChar(const QString& _char);
    void deleteChar();

    void setFontSize(unsigned size);
    void setFont(QString font);

    QPointF cursor();
    unsigned fontSize();

    private:
    unsigned m_fontSize;
    QString m_font;
    QVector<QString> m_text;
    raqm_direction_t m_direction = RAQM_DIRECTION_LTR;
    const char* m_language       = "en";
    QPointF m_cursor;
};

#endif // LAYOUT_HH
