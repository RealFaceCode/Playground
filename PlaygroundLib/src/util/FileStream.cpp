#include <../../hdr/util/FileStream.h>
#include "../../hdr/util/buffer/string.h"
#include "../../hdr/util/memory.h"
#include <../../hdr/logger.h>
#include <cstdio>
#include <direct.h>
#include <filesystem>
#include <sys/stat.h>
#include <io.h>
#include <share.h>

namespace FS
{
    bool createFile(const char* path)
    {
        if (path == nullptr)
        {
            return false;
        }
        int result = _creat(path, _S_IREAD | _S_IWRITE);
        if (result == -1 || !checkExistFile(path))
        {
            return false;
        }
        return true;
    }

    bool removeFile(const char* path)
    {
        if (path == nullptr || remove(path) != 0)
        {
            return false;
        }
        return true;
    }

    bool checkExistFile(const char* path)
    {
        if (path == nullptr)
        {
            return false;
        }
        return _access(path, 00) != -1;
    }

    bool renameFile(const char* path, const char* newName)
    {
        if (path == nullptr || newName == nullptr)
        {
            return false;
        }
        if (!checkExistFile(path))
        {
            return false;
        }
        if (rename(path, newName) != 0) {
            return false;
        }
        return true;
    }

    ui64 getFileSize(const char* path)
    {
        struct stat buf {};
        int c = stat(path, &buf);
        return c == 0 ? buf.st_size : 0;
    }

    bool createDir(const char* dirPath)
    {
        if (checkExistDir(dirPath))
        {
            return false;
        }
        return (_mkdir(dirPath) == 0);
    }

    bool removeDir(const char* dirPath)
    {
        if (!checkExistDir(dirPath))
        {
            return false;
        }
        return (_rmdir(dirPath) == 0);
    }

    bool checkExistDir(const char* dirPath)
    {
        if (dirPath == nullptr) return false;
        struct stat sb{};
        return (stat(dirPath, &sb) == 0 && (S_IFDIR & sb.st_mode) != 0);
    }

    void createDirIfNotExist(const char* dir)
    {
        //TODO: rewrite with String class
        std::string fullDirPath(dir);
        std::string dirPath;
        i64 position = 0;

        while (fullDirPath.size() >= position)
        {
            size_t off = fullDirPath.find('/', position);
            if(off == std::string::npos)
            {
                position = fullDirPath.end() - fullDirPath.begin();
                createDir(fullDirPath.c_str());
                return;
            }

            position = (i64)off;

            dirPath = std::string(fullDirPath.begin(), fullDirPath.begin() + position);
            createDir(dirPath.c_str());
            position++;
        }
    }

    bool checkIfDirContainsFiles(const char* dir)
    {
        return !std::filesystem::is_empty(dir);
    }

    uint64_t getFileCountFromDir(const char* dir)
    {
        uint64_t count = 0;
        for (auto entry : std::filesystem::directory_iterator(dir))
        {
            count++;
        }
        return count;
    }

    String getFileName(const char* filePath)
    {
        if(filePath == nullptr)
        {
            return {""};
        }

        String name(filePath);
        auto offset = name.find("/").back();
        name.remove(0, offset + 1);
        offset = name.find(".").back();
        name.remove(offset, name.length());
        return name;
    }

    String getFileNameExtension(const char* filePath)
    {
        if(filePath == nullptr)
        {
            return {""};
        }

        String nameExt(filePath);
        ui64 offset = nameExt.find("/").back();
        nameExt.remove(0, offset + 1);
        return nameExt;
    }

    std::vector<String> getFileNamesFromDir(const char* dir)
    {
        std::vector<String> fileNames;
        for (const auto& entry : std::filesystem::directory_iterator(dir))
        {
            auto path = entry.path().generic_string();
            uint64_t offset = path.find_last_of('/');
            path.erase(path.begin(), path.begin() + (long long)offset + 1);
            fileNames.emplace_back(path);
        }
        return fileNames;
    }

    std::vector<String> getFilePathsFromDir(const char* dir)
    {
        std::vector<String> filePaths;
        for (const auto& entry : std::filesystem::directory_iterator(dir))
        {
            filePaths.emplace_back(entry.path().generic_string());
        }
        return filePaths;
    }

    bool WriteToFile(const void* data, const ui64& bufLen, const char* filePath)
    {
        if(!data)
        {
            LOG_ERROR({}, "Failed to write to file with path'%S'! buffer is nullptr!", filePath);
            return false;
        }

        if(!checkExistFile(filePath))
        {
            if(!createFile(filePath))
            {
                LOG_ERROR({}, "Failed to create file and write to file with path'%S'!", filePath);
                return false;
            }
        }

        if(bufLen <= 0)
        {
            LOG_ERROR({}, "Failed to write to file, buffer is empty!");
            return false;
        }

        FILE* file = _fsopen(filePath, "wb", _SH_DENYNO);;
        if(!file)
        {
            LOG_ERROR({}, "Failed to open file with path'%s'", filePath);
            return false;
        }

        size_t result = fwrite(data, bufLen, 1, file);
        fclose(file);
        if(result != 1)
        {
            LOG_ERROR({}, "Failed to write to file with path'%s'", filePath);
            return false;
        }
        return true;
    }

    bool ReadFromFile(void** data, const char* filePath, const bool& nullTerm)
    {
        if(!checkExistFile(filePath))
        {
            LOG_ERROR({}, "File with path'%s' not found!", filePath);
            return false;
        }

        ui64 fileSize = getFileSize(filePath);
        if(fileSize <= 0)
        {
            LOG_ERROR({}, "File with path'%s' is empty!", filePath);
            return false;
        }

        FILE* file = _fsopen(filePath, "rb", _SH_DENYNO);;
        if(!file)
        {
            LOG_ERROR({}, "Failed to open file with path'%s'", filePath);
            return false;
        }

        if(nullTerm)
        {
            fileSize++;
        }

        *data = Malloc(fileSize);
        if(*data == nullptr)
        {
            LOG_ERROR({}, "Failed to allocate memory for file with path'%s'", filePath);
            return false;
        }

        size_t result = fread_s(*data, fileSize, fileSize - 1, 1, file);
        fclose(file);

        if(result == 0)
        {
            LOG_ERROR({}, "Failed to read data from file with path'%s'", filePath);
            Free(*data);
            *data = nullptr;
            return false;
        }
        char* cData;
        if(nullTerm)
        {
            cData = (char*)*data;
            cData[fileSize - 1] = '\0';
        }

        return true;
    }

    File::File()
        :mPath(""), mName(""), mEnding(""), mSource(0), mExist(false)
    {}

    File::File(const char* path, int flags)
        :mPath(path), mName(getFileName(path)), mEnding(getFileNameExtension(path)), mSource(0),mExist(checkExistFile(path))
    {
        if ((flags & FILE_CRT) == FILE_CRT)
        {
           createDirsAndFile();
        }

        if ((flags & FILE_READ) == FILE_READ)
        {
            read();
        }

        if ((flags & FILE_CLR) == FILE_CLR)
        {
            mSource.clear();
        }
    }

    File::~File()
    {
        mExist = false;
    }

    void File::read()
    {
        const char* filePath = (const char *)mPath.getSource();
        char* buffer = nullptr;
        ReadFromFile((void**)&buffer ,filePath, true);
        if(buffer)
        {
            mSource.add(buffer, true);
            Free(buffer);
        }
    }

    void File::write()
    {
        const char* filePath = (const char *)mPath.getSource();
        WriteToFile(mSource.getSource(), mSource.length(), filePath);
    }

    const String& File::getPath() const
    {
        return mPath;
    }

    const String& File::getName() const
    {
        return mName;
    }

    const String& File::getFileEnding() const
    {
        return mEnding;
    }

    BinaryBuffer &File::getData() {
        return mSource;
    }

    const ui64& File::capacity() const
    {
        return mSource.capacity();
    }

    const ui64& File::length() const
    {
        return mSource.length();
    }

    bool File::exist() const
    {
        return mExist;
    }

    ui8* File::getData(const ui64& len)
    {
        return (ui8*)mSource.pop(len);
    }

    i8 File::getI8()
    {
        return mSource.getI8();
    }

    ui8 File::getUI8()
    {
        return mSource.getUi8();
    }

    i16 File::getI16()
    {
        return mSource.getI16();
    }

    ui16 File::getUI16()
    {
        return mSource.getUi16();
    }

    i32 File::getI32()
    {
        return mSource.getI32();
    }

    ui32 File::getUI32()
    {
        return mSource.getUi32();
    }

    i64 File::getI64()
    {
        return mSource.getI64();
    }

    ui64 File::getUI64()
    {
        return mSource.getUi64();
    }

    bool File::getBool()
    {
        return (bool)mSource.getI8();
    }

    f32 File::getFloat()
    {
        return mSource.getF32();
    }

    f64 File::getDouble()
    {
        return mSource.getF64();
    }

    String File::getString(const bool& withoutLen)
    {
        return mSource.getString(withoutLen);
    }

    void File::addData(void* dat, const ui64& len)
    {
        mSource.push(len, dat);
    }

    void File::addI8(const i8& dat)
    {
        mSource.add(dat);
    }

    void File::addUI8(const ui8& dat)
    {
        mSource.add(dat);
    }

    void File::addI16(const i16& dat)
    {
        mSource.add(dat);
    }

    void File::addUI16(const ui16& dat)
    {
        mSource.add(dat);
    }

    void File::addI32(const i32& dat)
    {
        mSource.add(dat);
    }

    void File::addUI32(const ui32& dat)
    {
        mSource.add(dat);
    }

    void File::addI64(const i64& dat)
    {
        mSource.add(dat);
    }

    void File::addUI64(const ui64& dat)
    {
        mSource.add(dat);
    }

    void File::addBool(const bool& dat)
    {
        mSource.add((i8)dat);
    }

    void File::addF32(const f32& dat)
    {
        mSource.add(dat);
    }

    void File::addF64(const f64& dat)
    {
        mSource.add(dat);
    }

    void File::addString(const String& dat, const bool& withoutLen)
    {
        mSource.add(dat, withoutLen);
    }

    void File::addString(const std::string& dat, const bool& withoutLen)
    {
        mSource.add(dat, withoutLen);
    }

    void File::addString(const char* dat, const bool& withoutLen)
    {
        mSource.add(dat, withoutLen);
    }

    void File::createDirsAndFile()
    {
        if(!mExist)
        {
            ui64 lenRemove = mName.length() + mEnding.length() + 2;
            String dirPath(mPath);
            dirPath.remove(dirPath.length() - lenRemove, dirPath.length());
            createDirIfNotExist(dirPath.c_str());
            if(!(mExist = createFile(mPath.c_str())))
            {
                LOG_ASSERT(false, {}, "Failed to create file with path: %s", mPath.c_str())
            }
        }
    }
}