#include "layoutengine.hh"
#include "textchunk.hh"
#include <QDebug>

LayoutEngine::~LayoutEngine()
{
    raqm_destroy(m_rq);
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_library);
}

std::tuple<raqm_glyph_t*, size_t>
LayoutEngine::calculate(TextChunk& chunk)
{
    if (chunk.text().isEmpty() || chunk.fontSize() == 0 || chunk.text().isEmpty())
        return {};

    Q_ASSERT(FT_Init_FreeType(&m_library) == 0);
    Q_ASSERT(FT_New_Face(m_library, chunk.font().toUtf8().data(), 0, &m_face) == 0);
    Q_ASSERT(FT_Set_Char_Size(m_face, chunk.fontSize() * 64, 0, 0, 0) == 0);

    m_rq = raqm_create();
    Q_ASSERT(m_rq);

    auto charBytes = chunk.text().toUtf8();

    raqm_set_text_utf8(m_rq, charBytes, static_cast<size_t>(charBytes.size()));
    Q_ASSERT(raqm_set_freetype_face(m_rq, m_face));
    Q_ASSERT(raqm_set_par_direction(m_rq, chunk.direction()));
    Q_ASSERT(raqm_set_language(m_rq, chunk.language(), 0, static_cast<size_t>(charBytes.size())));
    Q_ASSERT(raqm_layout(m_rq));

    size_t count;
    raqm_glyph_t* glyphs = raqm_get_glyphs(m_rq, &count);

    Q_ASSERT(glyphs);
    Q_ASSERT(count > 0);

    return { glyphs, count };
}
