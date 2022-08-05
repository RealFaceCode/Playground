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
        void AddFile(const char* filePath);
        SpriteSheet LoadSpriteSheet(const char* filePath);
        SpriteSheet CreateSpriteSheet(const char* name, const bool& forceOverWrite = false);
    }

    namespace ImageHandler
    {
        const Image* GetImage(const char* imageName);
        void AddImage(const char* imagePath);
        void AddImages(const char* dirPath);
    }

    namespace SpriteSheetHandler
    {
        const SpriteSheet* GetSheet(const char* sheetName);
        const Sprite* getSpriteFromSheet(const char* sheetName, const char* spriteName);
        void AddSheet(const char* sheetPath);
        void AddSheets(const char* dirPath);
        void AddRawToSheet(const char* sheetName, const char* dirPath);
    }
}
#endif //PLAYGROUNDLIB_IMAGE_H
