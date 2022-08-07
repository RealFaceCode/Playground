//
// Created by Kevin-Laptop on 02.08.2022.
//
#include "../core.h"
#include "gfx.h"

#ifndef PLAYGROUNDLIB_IMAGE_H
#define PLAYGROUNDLIB_IMAGE_H

namespace GFX
{
    namespace ImageSettingsBuilder
    {
        enum ImageType
        {
            IMAGE2D
        };

        enum ImageInternalFormat
        {
            RGB32F,
            RGBA32F
        };

        enum ImageFormat
        {
            RGB,
            RGBA
        };

        enum ImageWrap
        {
            REPEAT
        };

        enum ImageFilter
        {
            LINEAR,
            NEAREST
        };

        struct ImageBuildingSettings
        {
        public:
            ImageType mType;
            ImageInternalFormat mInternalFormat;
            ImageFormat mFormat;
            ImageWrap mWrapS;
            ImageWrap mWrapT;
            ImageFilter mFilterMin;
            ImageFilter mFilterMag;
        };

        void AddNewBuildingSettings(const char* settingsName);
        void SetImageType(const char* settingsName, const ImageType& imageType);
        void SetImageInternalFormat(const char* settingsName, const ImageInternalFormat& internalFormat);
        void SetImageFormat(const char* settingsName, const ImageFormat& imageFormat);
        void SetImageWrapS(const char* settingsName, const ImageWrap& wrapS);
        void SetImageWrapT(const char* settingsName, const ImageWrap& wrapT);
        void SetImageFilterMin(const char* settingsName, const ImageFilter& min);
        void SetImageFilterMag(const char* settingsName, const ImageFilter& mag);
        Result<ImageBuildingSettings&> GetImageBuildingSettings(const char* settingsName);
    }

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