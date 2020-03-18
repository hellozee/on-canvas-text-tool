#ifndef LAYOUTENGINE_HH
#define LAYOUTENGINE_HH

#include "layout.hh"
#include <QGlyphRun>
#include <QRawFont>
#include <tuple>

class LayoutEngine {
    public:
    ~LayoutEngine();
    QGlyphRun calculate(const Layout& layout);

    private:
    raqm_t* m_rq;
    FT_Face m_face;
    FT_Library m_library;
};

#endif // LAYOUTENGINE_HH
