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
    void draw(QPainter& gc, QPointF topLeft, bool drawCursor);

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
    qreal cursorOffset();
    void setCursorOffset(qreal offset);

    private:
    QString m_text;
    unsigned m_fontSize, m_currentPos = 0;
    QString m_font;
    LayoutEngine m_layoutEngine;
    raqm_direction_t m_direction;
    char* m_language = "en";
    QGlyphRun m_glyphRun;
    raqm_glyph_t* m_glyphs;
    size_t m_glyphCount = 0;
    qreal m_cursorOffset;
};

#endif // TEXTCHUNK_HH
