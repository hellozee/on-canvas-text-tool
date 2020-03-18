#ifndef LAYOUTENGINE_HH
#define LAYOUTENGINE_HH

#include "layout.hh"
#include <QGlyphRun>
#include <QRawFont>
#include <tuple>

class LayoutEngine {
    public:
    QGlyphRun calculate(const Layout& layout);
};

#endif // LAYOUTENGINE_HH
