#ifndef __RANDOM_H__
#define __RANDOM_H__
#include "../core.h"
#include "../util/buffer/string.h"

namespace MATH
{
    template<typename Type>
    Type GetRandomNumber(const Type& min, const Type& max);

    template<typename Type>
    glm::vec2 GetRandomVec2(const Type& min, const Type& max);

    template<typename Type>
    glm::vec3 GetRandomVec3(const Type& min, const Type& max);

    template<typename Type>
    glm::vec4 GetRandomVec4(const Type& min, const Type& max);
}

#endif // __RANDOM_H__