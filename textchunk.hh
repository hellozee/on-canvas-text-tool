#ifndef TEXTCHUNK_HH
#define TEXTCHUNK_HH

#include "layoutengine.hh"
#include <QPainter>
#include <QRect>
#include <raqm.h>

class TextChunk {
    public:
    void addChar(QString _char);
    bool deleteChar();
    void draw(QPainter& gc, QPointF topLeft);

    void setFont(QString font);
    void setFontSize(unsigned size);

    QString text();
    QString font();
    raqm_direction_t direction();
    char* language();
    unsigned fontSize();
    QRectF boundingRect();

    bool cursorToLeft();
    bool cursorToRight();
    void calculatePositions();

    private:
    QString m_text;
    unsigned m_fontSize, m_currentPos;
    QString m_font;
    LayoutEngine m_layoutEngine;
    raqm_direction_t m_direction;
    char* m_language = "en";
    QGlyphRun m_glyphRun;
};

#endif // TEXTCHUNK_HH
