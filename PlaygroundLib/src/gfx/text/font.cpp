#include "../../hdr/gfx/text/font.h"
#include "../../hdr/util/FileStream.h"
#include "OpenGL.h"
#include "../../hdr/logger.h"

#ifndef STB_TRUETYPE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#endif

namespace GFX
{

    struct FontBitmask
    {
        f32 mSize;
        ui32 mTexID;
        stbtt_bakedchar mCharData[96];
    };

    float BMS_EnumToSize(const BitmaskSize& bms)
    {
        return (f32)bms;
    }

    Font::Font(const String& path)
    {
        void* load = nullptr;
        ui64 len;
        FS::ReadFromFile(&load, path.c_str(), &len);
        mFontData = (ui8*)load;
    }

    Font::Font(const String& path, const BitmaskSize& bms)
    {
        void* load = nullptr;
        ui64 len;
        FS::ReadFromFile(&load, path.c_str(), &len);
        mFontData = (ui8*)load;
        addNewFontSize(bms);
    }

    Font::~Font()
    {
        Free(mFontData);
    }
    
    void Font::addNewFontSize(const BitmaskSize&  bms)
    {
        f32 fontSize = BMS_EnumToSize(bms);
        FontBitmask fbm;
        fbm.mSize = fontSize;
        ui8 tmpBitmap[512 * 512];
        stbtt_BakeFontBitmap(mFontData, 0, fontSize, tmpBitmap, 512, 512, 32, 96, fbm.mCharData);

        glGenTextures(1, &fbm.mTexID);
        glBindTexture(GL_TEXTURE_2D, fbm.mTexID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, tmpBitmap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        mBitsmasks.add((BitmaskSize)fontSize, fbm);
    }

    FontBitmask& Font::getBitmask(const BitmaskSize& bms)
    {
        if(mBitsmasks.contains(bms))
        {
            return mBitsmasks.find(bms)->second;
        }
        addNewFontSize(bms);
        auto r = mBitsmasks.end().end() - 1;
        return r->second;
    }
}

#include "../../hdr/gfx/text/renderable_text.h"
#include "../../hdr/gfx/quad.h"
namespace GFX
{
    RenderableText::RenderableText(const ui32& x, const ui32& y, const BitmaskSize& bms, Font& font, const String& text, const ui32& maxLineLenPx)
        : mX(x), mY(y), mText(text), mMaxLineLenPx(maxLineLenPx)
    {
        mBitmask = &font.getBitmask(bms);
        mTextureID = mBitmask->mTexID;
    }

    RenderableText::~RenderableText()
    {}

    List<BatchVertex2D>& RenderableText::getRenderData()
    {
        return mRenderData;
    }

    ui32 RenderableText::textureID() const
    {
        return mTextureID;
    }

    ui32 RenderableText::verticesCount() const
    {
        return mText.length() * 6;
    }

    void RenderableText::prepareRenderData(const ui32& mapedTextureID)
    {
        f32 xb = 0;
        f32 yb = 0;
        f32 xOff = 0;

        List<GFX::Quad> quads;

        for(ui64 i = 0; i < mText.length(); i ++)
        {
            char c = mText.at(i);
            if(c >= 32 && c <= 128)
            {
                stbtt_aligned_quad q;
                stbtt_GetBakedQuad(mBitmask->mCharData, 512, 512, c - 32, &xb, &yb, &q, 1);
                if(i == 0)
                {
                    xOff = q.x0;
                }
                quads.add(GFX::Quad{q.x0 - xOff, q.y0, ((q.x1-q.x0)), (q.y1-q.y0), 0, q.s0, q.s1, q.t0, q.t1, 1, 1, 1, 1, (float)mapedTextureID});
            }
            else
            {
                LOG_WARNING({C_HiLi("%c", Red, 0), C_HiLi("%i", Red, 0)}, "the char [%c:%i] is not supported", c, (int)c);
            }
        }
        f32 cY = mY + (mBitmask->mSize * 0.625f);
        mRenderData = GetQuads_BV2D(mX, cY, 1, 1, 0, quads);
    }

    void RenderableText::SetText(const String &text)
    {
        mText = text;
    }

    void RenderableText::SetBMS(const BitmaskSize &bms)
    {
        mBitmask = nullptr;
    }

}