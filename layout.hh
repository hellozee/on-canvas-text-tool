#ifndef LAYOUT_HH
#define LAYOUT_HH

#include <QFont>
#include <QPainter>
#include <raqm.h>

class Layout {
    friend class LayoutEngine;

    public:
    void draw(QPainter& gc, const QPointF& pos, const QRect& clipRect);
    void addChar(const QString& _char);
    void deleteChar();

    void setFontSize(unsigned size);
    void setFont(QString font);

    private:
    unsigned m_fontSize;
    QString m_font, m_text;
    raqm_direction_t m_direction = RAQM_DIRECTION_LTR;
    const char* m_language       = "en";
};

#endif // LAYOUT_HH
