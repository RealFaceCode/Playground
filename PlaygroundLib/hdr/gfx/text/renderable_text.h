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

        List<BatchVertex2D>& getRenderData();
        ui32 textureID() const;
        ui32 verticesCount() const;

        void prepareRenderData(const ui32& mapedTextureID);
    private:
        List<BatchVertex2D> mRenderData;
        ui32 mTextureID;
        ui32 mX;
        ui32 mY;
        String mText;
        ui32 mMaxLineLenPx;
        FontBitmask* mBitmask;
    };
}

#endif // __RENDERABLE_TEXT_H__