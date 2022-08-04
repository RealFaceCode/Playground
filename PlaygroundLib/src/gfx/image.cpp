//
// Created by Kevin-Laptop on 02.08.2022.
//

#include "../../hdr/core.h"
#include "../../hdr/gfx/image.h"
#include <stb_image.h>
#include <stb_image_write.h>

namespace GFX
{
    Image::Image(const char* path)
    {
        unsigned char* texData = stbi_load(path, &mWidth, &mHeight, &mComp, 0);
        if (texData == nullptr)
        {
            log_fmt_error("Failed to create Texture with path'%s'", path);
            return;
        }


        ui32 format = mComp == 3 ? GL_RGB : GL_RGBA;
        ui32 internalType = mComp == 3 ? GL_RGB32F : GL_RGBA32F;

        glGenTextures(1, &mId);
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexImage2D(GL_TEXTURE_2D, 0, internalType, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, texData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(texData);
    }

    Image::Image(const unsigned char* data, ui32 width, ui32 height, ui32 comp)
            :mWidth(width), mHeight(height), mComp(comp)
    {
        if (data == nullptr)
        {
            log_error("Failed to create Texture!")
            return;
        }

        ui32 format = GL_RGBA;
        ui32 internalType = GL_RGBA8;

        glGenTextures(1, &mId);
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexImage2D(GL_TEXTURE_2D, 0, internalType, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

    }

    Image::Image(const Image& image)
    {
        mId = image.mId;
        mWidth = image.mWidth;
        mHeight = image.mHeight;
        mComp = image.mComp;
    }

    void Image::bind()
    {
        glBindTexture(GL_TEXTURE_2D, mId);
    }

    void Image::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Image::clear()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &mId);
    }

    Image& Image::operator=(const Image& other)
    {
        mId = other.mId;
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        mComp = other.mComp;
        return *this;
    }

    namespace SpriteSheetBuilder
    {
        std::vector<std::string> mFilePaths;

        void addFile(const char* filePath)
        {
            for(const auto& path : mFilePaths)
            {
                if(path == std::string(filePath))
                {
                    log_fmt_warning("File with path'%s' was already in list", filePath);
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
                        log_fmt_error("Failed to load file in to sprite sheet: '%s", path.c_str());
                        continue;
                    }
                    data.emplace_back(dat);
                }
                paths.clear();
            }

            if(data.empty())
            {
                log_fmt_error("Failed to generate sprite sheet no source given");
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

        SpriteSheet createSpriteSheet(const char* name, const bool& forceOverWrite)
        {
            if(FHandle::checkExistFile(name) && !forceOverWrite)
            {
                mFilePaths.clear();
                return SpriteSheet{};
            }

            std::vector<FileData> data;
            loadAndSort(data, mFilePaths);

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

            SpriteSheet spSh;
            spSh.image.mWidth = maxImageWidth;
            spSh.image.mHeight = maxImageHeight;
            spSh.image.mComp = 4;

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

                {
                    Sprite sprite
                    {
                        .uv0 = {(float) ((float) pos.x / (float) maxImageWidth),
                                (float) ((float) pos.y / (float) maxImageHeight)},
                        .uv1 = {(float) ((float) (pos.x + image.mWidth) / (float) maxImageWidth),
                                (float) ((float) pos.y / (float) maxImageHeight)},
                        .uv2 = {(float) ((float) (pos.x + image.mWidth) / (float) maxImageWidth),
                                (float) ((float) (pos.y + image.mHeight) / (float) maxImageHeight)},
                        .uv3 = {(float) ((float) pos.x / (float) maxImageWidth),
                                (float) ((float) (pos.y + image.mHeight) / (float) maxImageHeight)},
                    };

                    auto r = spSh.mSprites.emplace(image.mName, sprite);
                }
            }

            {
                spSh.image = Image(imageBuffer, maxImageWidth, maxImageHeight, 4);
                for(auto& sprite : spSh.mSprites)
                {
                    sprite.second.mId = spSh.image.mId;
                }
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
            return spSh;
        }
    }
}
