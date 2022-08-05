//
// Created by Kevin-Laptop on 02.08.2022.
//
#include "../core.h"
#include "gfx.h"

#ifndef PLAYGROUNDLIB_IMAGE_H
#define PLAYGROUNDLIB_IMAGE_H

namespace GFX
{
    struct Image
    {
    public:
        ui32 mId;
        i32 mWidth;
        i32 mHeight;
        i32 mComp;

        Image() = default;
        Image(const char* path);
        Image(const unsigned char* data, ui32 width, ui32 height, ui32 comp);
        Image(const Image& image);
        ~Image() = default;

        void bind();
        void unbind();

        void clear();

        Image& operator=(const Image& other);
    };

    struct Sprite
    {
    public:
        ui32 mId;
        glm::vec2 uv0;
        glm::vec2 uv1;
        glm::vec2 uv2;
        glm::vec2 uv3;
    };

    struct SpriteSheet
    {
    public:
        std::unordered_map<std::string, Sprite> mSprites;
        Image image;
    };

    namespace SpriteSheetBuilder
    {
        void addFile(const char* filePath);
        SpriteSheet createSpriteSheet(const char* name, const bool& forceOverWrite = false);
    }
}
#endif //PLAYGROUNDLIB_IMAGE_H
