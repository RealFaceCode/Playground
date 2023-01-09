#ifndef __FONT_H__
#define __FONT_H__

#include "../../core.h"
#include "../../util/buffer/map.h"
#include "../../util/buffer/string.h"

namespace GFX
{
    enum BitmaskSize : ui32
    {
        BMS2 = 2,
        BMS4 = 4,
        BMS6 = 6,
        BMS8 = 8,
        BMS10 = 10,
        BMS12 = 12,
        BMS14 = 14,
        BMS16 = 16,
        BMS18 = 18,
        BMS20 = 20,
        BMS22 = 22,
        BMS24 = 24,
        BMS26 = 26,
        BMS28 = 28,
        BMS30 = 30,
        BMS32 = 32,
        BMS34 = 34,
        BMS36 = 36,
        BMS38 = 38,
        BMS40 = 40,
        BMS42 = 42,
        BMS44 = 44,
        BMS46 = 46,
        BMS48 = 48,
        BMS50 = 50,
        BMS52 = 52,
        BMS54 = 54,
        BMS56 = 56,
        BMS58 = 58,
        BMS60 = 60,
        BMS62 = 62,
        BMS64 = 64,
    };

    float BMS_EnumToSize(const BitmaskSize& bms);

    struct FontBitmask;

    struct Font
    {
    public:
        Font() = default;
        Font(const String& path);
        Font(const String& path, const BitmaskSize& bms);
        ~Font();
        
        void addNewFontSize(const BitmaskSize&  bms);
        FontBitmask& getBitmask(const BitmaskSize& bms);

    private:
        ui8* mFontData;
        Map<BitmaskSize, FontBitmask> mBitsmasks;
    };
}

#endif // __FONT_H__