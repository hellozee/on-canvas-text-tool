#ifndef TEXTLINE_HH
#define TEXTLINE_HH

#include "textchunk.hh"

class TextLine {
    public:
    TextLine();
    QRect boundingRect();
    void draw(QPainter& gc, QPointF topLeft, bool lineDrawCursor);
    void addChar(QString _char);
    bool deleteChar();

    void setFont(QString font);
    void setFontSize(unsigned size);

    QVector<TextChunk> chunks();
    QVector<QString> words();
    unsigned currentChunkPos();

    bool cursorToLeft();
    bool cursorToRight();
    qreal cursorOffset();
    void setCursorOffset(qreal offset);

    TextLine newLine();
    void calculateChunks();

    private:
    QVector<TextChunk> m_textChunks;
    QRect m_boundingRect;
    unsigned m_currentChunk = 0;
};

#endif // TEXTLINE_HH
