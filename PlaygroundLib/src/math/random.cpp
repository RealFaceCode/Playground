#include "../../hdr/math/random.h"
#include "random"

namespace MATH
{

    template<typename Type>
    Type GetRandomNumber(const Type& min, const Type& max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return (Type)dis(gen);
    }
    
    template i8     GetRandomNumber<i8>(const i8&, const i8&);
    template i16    GetRandomNumber<i16>(const i16&, const i16&);
    template i32    GetRandomNumber<i32>(const i32&, const i32&);
    template i64    GetRandomNumber<i64>(const i64&, const i64&);
    template ui8    GetRandomNumber<ui8>(const ui8&, const ui8&);
    template ui16   GetRandomNumber<ui16>(const ui16&, const ui16&);
    template ui32   GetRandomNumber<ui32>(const ui32&, const ui32&);
    template ui64   GetRandomNumber<ui64>(const ui64&, const ui64&);
    template f32    GetRandomNumber<f32>(const f32&, const f32&);
    template f64    GetRandomNumber<f64>(const f64&, const f64&);

    template<typename Type>
    glm::vec2 GetRandomVec2(const Type& min, const Type& max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return glm::vec2{dis(gen), dis(gen)};
    }

    template glm::vec2 GetRandomVec2<i8>(const i8&, const i8&);
    template glm::vec2 GetRandomVec2<i16>(const i16&, const i16&);
    template glm::vec2 GetRandomVec2<i32>(const i32&, const i32&);
    template glm::vec2 GetRandomVec2<i64>(const i64&, const i64&);
    template glm::vec2 GetRandomVec2<ui8>(const ui8&, const ui8&);
    template glm::vec2 GetRandomVec2<ui16>(const ui16&, const ui16&);
    template glm::vec2 GetRandomVec2<ui32>(const ui32&, const ui32&);
    template glm::vec2 GetRandomVec2<ui64>(const ui64&, const ui64&);
    template glm::vec2 GetRandomVec2<f32>(const f32&, const f32&);
    template glm::vec2 GetRandomVec2<f64>(const f64&, const f64&);

    template<typename Type>
    glm::vec3 GetRandomVec3(const Type& min, const Type& max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return glm::vec3{dis(gen), dis(gen), dis(gen)};
    }

    template glm::vec3 GetRandomVec3<i8>(const i8&, const i8&);
    template glm::vec3 GetRandomVec3<i16>(const i16&, const i16&);
    template glm::vec3 GetRandomVec3<i32>(const i32&, const i32&);
    template glm::vec3 GetRandomVec3<i64>(const i64&, const i64&);
    template glm::vec3 GetRandomVec3<ui8>(const ui8&, const ui8&);
    template glm::vec3 GetRandomVec3<ui16>(const ui16&, const ui16&);
    template glm::vec3 GetRandomVec3<ui32>(const ui32&, const ui32&);
    template glm::vec3 GetRandomVec3<ui64>(const ui64&, const ui64&);
    template glm::vec3 GetRandomVec3<f32>(const f32&, const f32&);
    template glm::vec3 GetRandomVec3<f64>(const f64&, const f64&);

    template<typename Type>
    glm::vec4 GetRandomVec4(const Type& min, const Type& max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return glm::vec4{dis(gen), dis(gen), dis(gen), dis(gen)};
    }

    template glm::vec4 GetRandomVec4<i8>(const i8&, const i8&);
    template glm::vec4 GetRandomVec4<i16>(const i16&, const i16&);
    template glm::vec4 GetRandomVec4<i32>(const i32&, const i32&);
    template glm::vec4 GetRandomVec4<i64>(const i64&, const i64&);
    template glm::vec4 GetRandomVec4<ui8>(const ui8&, const ui8&);
    template glm::vec4 GetRandomVec4<ui16>(const ui16&, const ui16&);
    template glm::vec4 GetRandomVec4<ui32>(const ui32&, const ui32&);
    template glm::vec4 GetRandomVec4<ui64>(const ui64&, const ui64&);
    template glm::vec4 GetRandomVec4<f32>(const f32&, const f32&);
    template glm::vec4 GetRandomVec4<f64>(const f64&, const f64&);
}