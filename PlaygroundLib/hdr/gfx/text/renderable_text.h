#ifndef __RENDERABLE_TEXT_H__
#define __RENDERABLE_TEXT_H__
#include "word.h"
#include "font.h"
#include "../../util/buffer/string.h"
#include "../batchrenderer/batchvertex.h"

namespace GFX
{
    struct RenderableText
    {
    public:
        RenderableText() = default;
        RenderableText(const ui32& x, const ui32& y, const BitmaskSize& bms, Font& font, const String& text, const ui32& maxLineLenPx);
        ~RenderableText();
        List<Pair<glm::vec2, glm::vec2>>& getRenderData();
        ui32 textureID();
    private:
        void prepareRenderData(List<Pair<glm::vec2, glm::vec2>>& gl, const float& mTextureID);

    private:
        List<Pair<glm::vec2, glm::vec2>> mRenderData;
        ui32 mTextureID;
    };
}

#endif // __RENDERABLE_TEXT_H__