#include "../../hdr/core.h"
#include "../../hdr/logger.h"
#include "../../hdr/gfx/image.h"
#include <stb_image.h>
#include <stb_image_write.h>
#include <OpenGL.h>

namespace GFX
{
    namespace ImageSettingsBuilder
    {
        static std::unordered_map<std::string, ImageBuildingSettings> imgBuildingSettings;

        static ImageBuildingSettings defaultImageBuildingSetting
        {
            .mType              = ImageType::IMAGE2D,
            .mInternalFormat    = ImageInternalFormat::AUTO,
            .mFormat            = ImageFormat::AUTO,
            .mWrapS             = ImageWrap::REPEAT,
            .mWrapT             = ImageWrap::REPEAT,
            .mFilterMin         = ImageFilter::LINEAR,
            .mFilterMag         = ImageFilter::LINEAR
        };

        const i32 ImageBuildingSettings::convertType() const
        {
            switch (mType) {
                case ImageType::IMAGE2D:
                    return GL_TEXTURE_2D;
                    break;
            }
        }

        const i32 ImageBuildingSettings::convertInternalFormat() const
        {
            switch (mInternalFormat) {
                case ImageInternalFormat::AUTO:
                    return -1;
                    break;
                case ImageInternalFormat::RGB8:
                    return GL_RGB8;
                    break;
                case ImageInternalFormat::RGBA8:
                    return GL_RGBA8;
                    break;
                case ImageInternalFormat::RGB32F:
                    return GL_RGB32F;
                    break;
                case ImageInternalFormat::RGBA32F:
                    return GL_RGBA32F;
                    break;
            }
        }

        const i32 ImageBuildingSettings::convertFormat() const
        {
            switch (mFormat) {
                case ImageFormat::AUTO:
                    return -1;
                    break;
                case ImageFormat::RGB:
                    return GL_RGB;
                    break;
                case ImageFormat::RGBA:
                    return GL_RGBA;
                    break;
            }
        }

        const i32 ImageBuildingSettings::convertWrapS() const
        {
            switch (mWrapS) {
                case ImageWrap::REPEAT:
                    return GL_REPEAT;
                    break;
            }
        }

        const i32 ImageBuildingSettings::convertWrapT() const
        {
            switch (mWrapT) {
                case ImageWrap::REPEAT:
                    return GL_REPEAT;
                    break;
            }
        }

        const i32 ImageBuildingSettings::convertMin() const
        {
            switch (mFilterMin) {
                case ImageFilter::LINEAR:
                    return GL_LINEAR;
                    break;
                case ImageFilter::NEAREST:
                    return GL_NEAREST;
                    break;
            }
        }

        const i32 ImageBuildingSettings::convertMag() const
        {
            switch (mFilterMag) {
                case ImageFilter::LINEAR:
                    return GL_LINEAR;
                    break;
                case ImageFilter::NEAREST:
                    return GL_NEAREST;
                    break;
            }
        }

        void AddNewBuildingSettings(const char* settingsName)
        {
            if(settingsName == nullptr)
            {
                LOG_WARNING({}, "Failed to add a new building setting! settings name was nullptr!");
                return;
            }

            for(const auto& settings : imgBuildingSettings)
            {
                if(settings.first == std::string(settingsName))
                {
                    LOG_WARNING({}, "Failed to add a new building setting with name'%s'! settings name is already used!", settingsName);
                    return;
                }
            }

            imgBuildingSettings.emplace(std::string(settingsName), defaultImageBuildingSetting);
        }

        void SetImageType(const char* settingsName, const ImageType& imageType)
        {
            auto result = GetImageBuildingSettings(settingsName);
            if(!result)
            {
                LOG_WARNING({},
                            "Failed to set image type to image building settings with name'%s'! The default buildings setting was returned!",
                            settingsName);
                return;
            }

            auto& settings = result.unwrap();
            settings.mType = imageType;
        }

        void SetImageInternalFormat(const char* settingsName, const ImageInternalFormat& internalFormat)
        {
            auto result = GetImageBuildingSettings(settingsName);
            if(!result)
            {
                LOG_WARNING({},
                            "Failed to set image internal format to image building settings with name'%s'! The default buildings setting was returned!",
                            settingsName);
                return;
            }

            auto& settings = result.unwrap();
            settings.mInternalFormat = internalFormat;
        }

        void SetImageFormat(const char* settingsName, const ImageFormat& imageFormat)
        {
            auto result = GetImageBuildingSettings(settingsName);
            if(!result)
            {
                LOG_WARNING({},
                            "Failed to set image format to image building settings with name'%s'! The default buildings setting was returned!",
                            settingsName);
                return;
            }

            auto& settings = result.unwrap();
            settings.mFormat = imageFormat;
        }

        void SetImageWrapS(const char* settingsName, const ImageWrap& wrapS)
        {
            auto result = GetImageBuildingSettings(settingsName);
            if(!result)
            {
                LOG_WARNING({},
                            "Failed to set image warp s to image building settings with name'%s'! The default buildings setting was returned!",
                            settingsName);
                return;
            }

            auto& settings = result.unwrap();
            settings.mWrapS = wrapS;
        }

        void SetImageWrapT(const char* settingsName, const ImageWrap& wrapT)
        {
            auto result = GetImageBuildingSettings(settingsName);
            if(!result)
            {
                LOG_WARNING({},
                            "Failed to set image warp t to image building settings with name'%s'! The default buildings setting was returned!",
                            settingsName);
                return;
            }

            auto& settings = result.unwrap();
            settings.mWrapT = wrapT;
        }

        void SetImageFilterMin(const char* settingsName, const ImageFilter& min)
        {
            auto result = GetImageBuildingSettings(settingsName);
            if(!result)
            {
                LOG_WARNING({},
                            "Failed to set image min filter to image building settings with name'%s'! The default buildings setting was returned!",
                            settingsName);
                return;
            }

            auto& settings = result.unwrap();
            settings.mFilterMin = min;
        }

        void SetImageFilterMag(const char* settingsName, const ImageFilter& mag)
        {
            auto result = GetImageBuildingSettings(settingsName);
            if(!result)
            {
                LOG_WARNING({},
                            "Failed to set image mag filter to image building settings with name'%s'! The default buildings setting was returned!",
                            settingsName);
                return;
            }

            auto& settings = result.unwrap();
            settings.mFilterMag = mag;
        }

        Result<ImageBuildingSettings&> GetImageBuildingSettings(const char* settingsName)
        {
            for(auto& settings : imgBuildingSettings)
            {
                if(settings.first == std::string(settingsName))
                {
                    return {settings.second, true};
                }
            }

            return {defaultImageBuildingSetting, false};
        }
    }

    Image::Image(const char* path, const char* settingsName)
    {
        CHECK_INIT_GFX
        stbi_set_flip_vertically_on_load(true);
        unsigned char* texData = stbi_load(path, &mWidth, &mHeight, &mComp, 0);
        if (texData == nullptr)
        {
            LOG_ERROR({}, "Failed to create Texture with path'%s'", path);
            return;
        }

        auto result = ImageSettingsBuilder::GetImageBuildingSettings(settingsName);
        auto& s = result.unwrap();

        auto type           = s.convertType();
        auto internalFormat = s.convertInternalFormat();
        auto format         = s.convertFormat();
        auto wrapS          = s.convertWrapS();
        auto wrapT          = s.convertWrapT();
        auto min            = s.convertMin();
        auto mag            = s.convertMag();

        if(internalFormat == -1)
        {
            internalFormat = mComp == 3 ? GL_RGB32F : GL_RGBA32F;
        }

        if(format == -1)
        {
            format = mComp == 3 ? GL_RGB : GL_RGBA;
        }

        glGenTextures(1, &mId);
        glBindTexture(type, mId);
        glTexImage2D(type, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, texData);
        glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapT);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, mag);
        glBindTexture(type, 0);

        stbi_image_free(texData);
    }

    Image::Image(const unsigned char* data, ui32 width, ui32 height, ui32 comp, const char* settingsName)
            :mWidth(width), mHeight(height), mComp(comp)
    {
        CHECK_INIT_GFX

        if (data == nullptr)
        {
            LOG_ERROR({}, "Failed to create Texture!");
            return;
        }

        auto result = ImageSettingsBuilder::GetImageBuildingSettings(settingsName);
        auto& s = result.unwrap();

        auto type           = s.convertType();
        auto internalFormat = s.convertInternalFormat();
        auto format         = s.convertFormat();
        auto wrapS          = s.convertWrapS();
        auto wrapT          = s.convertWrapT();
        auto min            = s.convertMin();
        auto mag            = s.convertMag();

        if(internalFormat == -1)
        {
            internalFormat = mComp == 3 ? GL_RGB32F : GL_RGBA32F;
        }

        if(format == -1)
        {
            format = mComp == 3 ? GL_RGB : GL_RGBA;
        }

        glGenTextures(1, &mId);
        glBindTexture(type, mId);
        glTexImage2D(type, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapT);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, mag);
        glBindTexture(type, 0);
    }

    Image::Image(const Image& image)
    {
        CHECK_INIT_GFX

        mId = image.mId;
        mWidth = image.mWidth;
        mHeight = image.mHeight;
        mComp = image.mComp;
    }

    void Image::bind()
    {
        CHECK_INIT_GFX

        glBindTexture(GL_TEXTURE_2D, mId);
    }

    void Image::unbind()
    {
        CHECK_INIT_GFX

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Image::clear()
    {
        CHECK_INIT_GFX

        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &mId);
    }

    Image& Image::operator=(const Image& other)
    {
        CHECK_INIT_GFX

        mId = other.mId;
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        mComp = other.mComp;
        return *this;
    }

    namespace SpriteSheetBuilder
    {
        std::vector<std::string> mFilePaths;

        void AddFile(const char* filePath)
        {
            CHECK_INIT_GFX

            for(const auto& path : mFilePaths)
            {
                if(path == std::string(filePath))
                {
                    LOG_WARNING({}, "File with path'%s' was already in list", filePath);
                    return;
                }
            }
            mFilePaths.emplace_back(std::string(filePath));
        }

        struct FileData
        {
        public:
            std::string mName;
            ui8* mData;
            i32 mWidth;
            i32 mHeight;
            i32 mComp;

        public:
            bool operator>(const FileData& other) const
            {
                return (mWidth * mHeight) > (other.mWidth * other.mHeight);
            }
        };

        struct Position
        {
        public:
            i32 x;
            i32 y;
        };

        static void correctComponents(std::vector<FileData>& data)
        {
            for(auto& image : data)
            {
                if(image.mComp != 4)
                {
                    const ui64 size = image.mWidth * image.mHeight * 4;
                    ui8* ptr = new ui8[size];
                    memset(ptr, 255, size);
                    for(auto i = 0; i < size ; i ++)
                    {
                        auto check = (i + 1) % 4;
                        if(check)
                        {
                            ptr[i] = image.mData[i];
                        }
                    }
                    delete image.mData;
                    image.mData = nullptr;
                    image.mData = ptr;
                    image.mComp = 4;
                }
            }
        }

        static void getMaxDimension(i32& width, i32& height, const std::vector<FileData>& data)
        {
            if(data.size() > 1)
            {
                width = data.at(0).mWidth + data.at(1).mWidth;
            }
            else
            {
                width = data.at(0).mWidth;
            }

            height = data.at(0).mHeight;;
            ui32 tmpWidth = 0;
            for(auto image : data)
            {
                if(tmpWidth >= width)
                {
                    tmpWidth = 0;
                    height += image.mHeight;
                }
                tmpWidth += image.mWidth;
            }
        }

        static void loadAndSort(std::vector<FileData>& data, std::vector<std::string>& paths)
        {
            {
                data.reserve(paths.size());
                for(auto& path : paths)
                {
                    FileData dat{};
                    dat.mName = FHandle::getFileName(path.c_str());
                    dat.mData = stbi_load(path.c_str(), &dat.mWidth, &dat.mHeight, &dat.mComp, STBI_rgb_alpha);
                    if(dat.mData == nullptr)
                    {
                        LOG_ERROR({}, "Failed to load file in to sprite sheet: '%s", path.c_str());
                        continue;
                    }
                    data.emplace_back(dat);
                }
                paths.clear();
            }

            if(data.empty())
            {
                LOG_ERROR({}, "Failed to generate sprite sheet no source given");
                return;
            }


            for (const auto& i : data)
            {
                std::sort(data.begin(), data.end(), std::greater <>());
            }
        }

        Position getPosition(bool* tracker,
                             const ui32& wArr, const ui32& hArr,
                             const i32& wImage, const i32& hImage,
                             const ui32& wMax)
        {
            for(auto height = 0; height < hArr; height++)
            {
                for(auto width = 0; width < wArr; width++)
                {
                    bool track = tracker[(height * wMax)  + width];
                    if(!track)
                    {
                        if(width + wImage <= wMax)
                        {
                            bool foundFree = true;
                            for(auto hIn = height; hIn < height + hImage; hIn++)
                            {
                                for(auto wIn = width; wIn < width + wImage; wIn++)
                                {
                                    bool checkFree = tracker[(hIn * wMax) + wIn];
                                    if(checkFree)
                                    {
                                        foundFree = false;
                                        break;
                                    }
                                }
                                if(!foundFree)
                                {
                                    break;
                                }
                            }
                            if (foundFree)
                            {
                                for(auto hIn = height; hIn < height + hImage; hIn++)
                                {
                                    for(auto wIn = width; wIn < width + wImage; wIn++)
                                    {
                                        tracker[(hIn * wMax) + wIn] = true;
                                    }
                                }
                                return Position{.x = width, .y = height};
                            }
                        }
                    }
                }
            }
            return Position{.x = -1, .y = -1};
        }

        SpriteSheet LoadSpriteSheet(const char *filePath) {
            return SpriteSheet();
        }

        static void AddToSpriteSheet(SpriteSheet& sheet,
                                     const FileData& image,
                                     const Position& pos,
                                     const ui32& maxImageWidth,
                                     const ui32& maxImageHeight)
        {

            f32 x0 = (float) ((float)pos.x + 0.0) / (float) maxImageWidth;
            f32 y0 = (float) ((float)pos.y + 0.0)/ (float) maxImageHeight;
            f32 x1 = (float) ((float)(pos.x + image.mWidth) - 0.0) / (float) maxImageWidth;
            f32 y1 = (float) ((float)pos.y + 0.0) / (float) maxImageHeight;
            f32 x2 = (float) ((float)(pos.x + image.mWidth) - 0.0) / (float) maxImageWidth;
            f32 y2 = (float) ((float)(pos.y + image.mHeight) - 0.0) / (float) maxImageHeight;
            f32 x3 = (float) ((float)pos.x + 0.0)/ (float) maxImageWidth;
            f32 y3 = (float) ((float)(pos.y + image.mHeight) - 0.0) / (float) maxImageHeight;

            Sprite sprite
            {
                .uv0 = {x0, y0},
                .uv1 = {x1, y1},
                .uv2 = {x2, y2},
                .uv3 = {x3, y3},
            };

            sheet.mSprites.emplace(image.mName, sprite);
        }

        SpriteSheet CreateSpriteSheet(const char* name, const bool& forceOverWrite)
        {
            CHECK_INIT_GFX

            if(FHandle::checkExistFile(name) && !forceOverWrite)
            {
                mFilePaths.clear();
                return LoadSpriteSheet(name);
            }

            std::vector<FileData> data;
            loadAndSort(data, mFilePaths);

            if(data.empty())
            {
                return SpriteSheet();
            }

            i32 maxImageWidth = 0;
            i32 maxImageHeight = 0;
            getMaxDimension(maxImageWidth, maxImageHeight, data);
            correctComponents(data);

            ui64 maxSizeBuffer = maxImageHeight * maxImageWidth * 4;
            ui64 maxSizeTrackBuffer = maxImageHeight * maxImageWidth;
            ui8* imageBuffer =  new ui8[maxSizeBuffer];
            bool* trackBuffer =  new bool[maxSizeTrackBuffer];
            memset(imageBuffer, 0, maxSizeBuffer);
            memset(trackBuffer, 0, maxSizeTrackBuffer);

            std::queue<FileData> fileQueue;
            for(const auto& image : data)
            {
                fileQueue.emplace(image);
            }

            SpriteSheet sheet;
            sheet.image.mWidth = maxImageWidth;
            sheet.image.mHeight = maxImageHeight;
            sheet.image.mComp = 4;

            while(!fileQueue.empty())
            {
                const auto image = fileQueue.front();
                fileQueue.pop();
                Position pos = getPosition(trackBuffer, maxImageWidth, maxImageHeight,
                                           image.mWidth, image.mHeight,
                                           maxImageWidth);

                for(auto i = 0; i < image.mHeight; i++)
                {
                    memcpy(imageBuffer + ((i + pos.y) * (maxImageWidth * 4) + (pos.x * 4)),
                           image.mData + (i * image.mWidth * 4), image.mWidth * 4);
                }
                AddToSpriteSheet(sheet, image, pos, maxImageWidth, maxImageHeight);
            }

            sheet.image = Image(imageBuffer, maxImageWidth, maxImageHeight, 4, "defaultSpriteSheetSetting");
            for(auto& sprite : sheet.mSprites)
            {
                sprite.second.mId = sheet.image.mId;
            }

            stbi_write_png(name, maxImageWidth, maxImageHeight, 4, imageBuffer, 0);

            {
                for(auto& dat : data)
                {
                    stbi_image_free(dat.mData);
                }
                data.clear();

                delete[] imageBuffer;
                delete[] trackBuffer;
            }
            return sheet;
        }
    }

    namespace ImageHandler
    {
        std::unordered_map<std::string, Image> images;

        const Image* GetImage(const char* imageName)
        {
            CHECK_INIT_GFX

            if(images.find(std::string(imageName)) != images.end())
            {
                return &images.at(std::string(imageName));
            }

            LOG_WARNING({}, "Failed to get image with image name'%s'", imageName);
            return nullptr;
        }

        void AddImage(const char* imagePath, const char* settingsName)
        {
            CHECK_INIT_GFX
            if(!FHandle::checkExistFile(imagePath))
            {
                LOG_WARNING({}, "Failed to add image with image path'%s'", imagePath);
                return;
            }

            std::string imgName = FHandle::getFileName(imagePath);

            for(const auto& name : images)
            {
                if(name.first == imgName)
                {
                    LOG_WARNING({}, "Failed to add image with image path'%s'. File already added", imagePath);
                    return;
                }
            }

            images.emplace(imgName, Image(imagePath, settingsName));
        }

        void AddImages(const char* dirPath, const char* settingsName)
        {
            CHECK_INIT_GFX
            if(!FHandle::checkExistDir(dirPath))
            {
                LOG_WARNING({}, "Failed to add images from dir path'%s'", dirPath);
                return;
            }

            auto paths = FHandle::getFilePathsFromDir(dirPath);

            for(const auto& path : paths)
            {
                std::string imgName = FHandle::getFileName(path.c_str());
                bool add = true;
                for(const auto& name : images)
                {
                    if(name.first == imgName)
                    {
                        add = false;
                        LOG_WARNING({}, "Failed to add image with image path'%s'. File already added", path.c_str());
                        break;
                    }
                }

                if(add)
                {
                    images.emplace(imgName, Image(path.c_str(), settingsName));
                }
            }
        }
    }

    namespace SpriteSheetHandler
    {
        std::unordered_map<std::string, SpriteSheet> sheets;

        const SpriteSheet* GetSheet(const char* sheetName)
        {
            CHECK_INIT_GFX
            if(sheets.find(std::string(sheetName)) != sheets.end())
            {
                return (const SpriteSheet*)&sheets.at(std::string(sheetName));
            }
            return nullptr;
        }

        const Sprite* getSpriteFromSheet(const char* sheetName, const char* spriteName)
        {
            CHECK_INIT_GFX
            const auto* sheet = GetSheet(sheetName);
            if(sheet == nullptr)
            {
                return nullptr;
            }

            if(sheet->mSprites.find(spriteName) != sheet->mSprites.end())
            {
                return (const Sprite*)&sheet->mSprites.at(spriteName);
            }
            return nullptr;
        }

        void AddSheet(const char* sheetPath)
        {
            CHECK_INIT_GFX
            if(!FHandle::checkExistFile(sheetPath))
            {
                LOG_WARNING({}, "Failed to add sheet with path'%s'", sheetPath);
                return;
            }

            std::string sheetName = FHandle::getFileName(sheetPath);

            for(const auto& name : sheets)
            {
                if(name.first == sheetName)
                {
                    LOG_WARNING({}, "Failed to add sheet with path'%s'. File already added", sheetPath);
                    return;
                }
            }

            sheets.emplace(sheetName, SpriteSheetBuilder::LoadSpriteSheet(sheetPath));
        }

        void AddSheets(const char* dirPath)
        {
            CHECK_INIT_GFX
            if(!FHandle::checkExistDir(dirPath))
            {
                LOG_WARNING({}, "Failed to add sheets from path'%s'", dirPath);
                return;
            }

            auto paths = FHandle::getFilePathsFromDir(dirPath);

            for(const auto& path : paths)
            {
                std::string sheetName = FHandle::getFileName(path.c_str());

                for(const auto& name : sheets)
                {
                    if(name.first == sheetName)
                    {
                        LOG_WARNING({}, "Failed to add sheet with path'%s'. File already added", path.c_str());
                        return;
                    }
                }

                sheets.emplace(sheetName, SpriteSheetBuilder::LoadSpriteSheet(path.c_str()));
            }
        }

        void AddRawToSheet(const char* sheetName, const char* dirPath)
        {
            CHECK_INIT_GFX
            if(!FHandle::checkExistDir(dirPath))
            {
                LOG_WARNING({}, "Failed to create sheet from path'%s'", dirPath);
                return;
            }

            auto paths = FHandle::getFilePathsFromDir(dirPath);

            for(const auto& path : paths)
            {
                SpriteSheetBuilder::AddFile(path.c_str());
            }
            sheets.emplace(std::string(sheetName), SpriteSheetBuilder::CreateSpriteSheet(sheetName));
        }
    }
}