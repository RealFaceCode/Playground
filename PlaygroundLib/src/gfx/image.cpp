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

    void SpriteSheet::addFile(const char *filePath)
    {
        mFilePaths.emplace_back(std::string(filePath));
    }



    struct FileData
    {
    public:
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

    void getPosArrayAccessCpy(ui8* arr, int x, int y, int dimy, ui8* data, ui32 dataSize)
    {
        ui32 pos = x + (y * dimy);
        memcpy(arr + pos, data, dataSize);
    }

    void SpriteSheet::createSpriteSheet(const char* name)
    {
        std::vector<FileData> data;
        //load data
        {
            data.reserve(mFilePaths.size());
            for(auto& path : mFilePaths)
            {
                FileData dat{};
                dat.mData = stbi_load(path.c_str(), &dat.mWidth, &dat.mHeight, &dat.mComp, STBI_rgb_alpha);
                if(dat.mData == nullptr)
                {
                    log_fmt_error("Failed to load file in to spritesheed: '%s", path.c_str());
                    continue;
                }
                data.emplace_back(dat);
            }
            mFilePaths.clear();
        }

        if(data.empty())
        {
            log_fmt_error("Failed to generate spritesheet no source given");
        }

        //sort
        for (const auto& i : data)
        {
            std::sort(data.begin(), data.end(), std::greater <>());
        }

        //get maxImage width
        i32 maxImageWidth = 0;
        if(data.size() > 1)
        {
            maxImageWidth = data.at(0).mWidth + data.at(1).mWidth;
        }
        else
        {
            maxImageWidth = data.at(0).mWidth;
        }

        //get maxImage height
        i32 maxImageHeight = data.at(0).mHeight;
        ui32 tmpHeight = 0;
        ui32 tmpWidth = 0;
        for(auto image : data)
        {
            if(tmpWidth >= maxImageWidth)
            {
                tmpWidth = 0;
                maxImageHeight += image.mHeight;
            }
            tmpWidth += image.mWidth;
        }


        // correct data to 4 comp;
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

        //allocating buffer and zero mem
        ui64 maxSizeBuffer = maxImageHeight * maxImageWidth * 4;
        ui8* imageBuffer =  new ui8[maxSizeBuffer];
        memset(imageBuffer, 255, maxSizeBuffer);

        //queue
        std::queue<FileData> fileQueue;
        for(auto image : data)
        {
            fileQueue.emplace(image);
        }

        //fill data
        //Todo: get x and y coords
        ui32 x = 0;             // xPos
        ui32 y = 0;             // yPos
        ui32 calculatedY = 0;   // calculated y with offset ( (y + i) * maxImageWidth * components)
        bool canFitNextTo = false;
        ui32 prevImgHeight = 0;
        ui32 prevImgWidth = 0;
        ui32 trackHeight = 0;
        ui32 trackWidth = 0;
        FileData image{};

        while(!fileQueue.empty())
        {
            image = fileQueue.front();
            fileQueue.pop();

            ui32 width = image.mWidth;
            ui32 height = image.mHeight;
            ui32 comp = image.mComp;
            ui32 rowSize = width * comp;

            if(trackWidth + width <= maxImageWidth && !canFitNextTo)
            {
                canFitNextTo = true;
                x = prevImgWidth;
                y = trackHeight;
            }
            else if(trackWidth + width <= maxImageWidth && canFitNextTo)
            {
                x = trackWidth;
            }
            else
            {
                x = prevImgWidth;
                trackWidth = prevImgWidth;
            }

            if(trackHeight >= prevImgHeight)
            {
                canFitNextTo = false;
                prevImgWidth = 0;
                x = 0;
                trackWidth = 0;
            }

            for(auto i = 0; i < height; i++)
            {
                calculatedY = ((y + i) * maxImageWidth * comp);
                memcpy(imageBuffer + (calculatedY + x * 4), image.mData + (i * rowSize), rowSize);
            }

            if(canFitNextTo)
            {
                if(trackWidth + width >= maxImageWidth)
                {
                    trackHeight += height;
                    y += height;
                }

            }

            trackWidth += width;

            if(!canFitNextTo)
                prevImgWidth += width;


            if(!canFitNextTo)
            {
                prevImgHeight += height;
                x += width;
                y += height;
            }
        }

        //stbi_flip_vertically_on_write(true);
        stbi_write_png(name, maxImageWidth, maxImageHeight, 4, imageBuffer, 0);

        //clear data
        {
            //clearing vector filedata
            {
                for(auto& dat : data)
                {
                    stbi_image_free(dat.mData);
                }
                data.clear();
            }

        }
    }
}
