#ifndef __WORD_H__
#define __WORD_H__
#include "../../core.h"
#include "../../util/buffer/list.h"
#include "chararcter.h"

namespace GFX
{
    struct Word
    {
        f32 mWith;
        List<Character> mChars;
    };
}

#endif // __WORD_H__