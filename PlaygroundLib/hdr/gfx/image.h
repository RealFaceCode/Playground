//
// Created by Kevin-Laptop on 02.08.2022.
//
#include "../core.h"

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
        f32 uv0;
        f32 uv1;
        f32 uv2;
        f32 uv3;
    };

    struct SpriteSheet
    {
    public:
        std::unordered_map<std::string, Sprite> mSprites;
        std::vector<std::string> mFilePaths;

        void addFile(const char* filePath);
        void createSpriteSheet(const char* name);
    };

}
#endif //PLAYGROUNDLIB_IMAGE_H
