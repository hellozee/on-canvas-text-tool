#ifndef LAYOUTENGINE_HH
#define LAYOUTENGINE_HH

#include <QGlyphRun>
#include <QRawFont>
#include <raqm.h>
#include <tuple>

class TextChunk;

class LayoutEngine {
    public:
    ~LayoutEngine();
    std::tuple<raqm_glyph_t*, size_t> calculate(TextChunk& chunk);

    private:
    raqm_t* m_rq;
    FT_Face m_face;
    FT_Library m_library;
};

#endif // LAYOUTENGINE_HH
