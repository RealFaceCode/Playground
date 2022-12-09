#include <../../hdr/util/FileStream.h>
#include "../../hdr/util/buffer/string.h"
#include <../../hdr/logger.h>
#include <cstdio>
#include <direct.h>
#include <filesystem>
#include <sys/stat.h>
#include <io.h>

namespace FS
{
    bool createFile(const char* path) {
        if (path == nullptr) {
            return false;
        }
        int result = _creat(path, _S_IREAD | _S_IWRITE);
        if (result == -1 || !checkExistFile(path)) {
            return false;
        }
        return true;
    }

    bool removeFile(const char* path) {
        if (path == nullptr || remove(path) != 0) {
            return false;
        }
        return true;
    }

    bool checkExistFile(const char* path) {
        if (path == nullptr) return false;
        return _access(path, 00) != -1;
    }

    bool renameFile(const char* path, const char* newName) {
        if (path == nullptr || newName == nullptr) {
            return false;
        }
        if (!checkExistFile(path)) {
            return false;
        }
        if (rename(path, newName) != 0) {
            return false;
        }
        return true;
    }

    uint64_t getFileSize(const char* path) {
        struct stat buf {};
        int c = stat(path, &buf);
        return c == 0 ? buf.st_size : 0;
    }

    bool createDir(const char* dirPath) {
        if (checkExistDir(dirPath)) return false;
        return (_mkdir(dirPath) == 0);
    }

    bool removeDir(const char* dirPath) {
        if (!checkExistDir(dirPath)) return false;
        return (_rmdir(dirPath) == 0);
    }

    bool checkExistDir(const char* dirPath) {
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

    File::File()
        :mPath(""), mName(""), mEnding(""), mSource(0), mExist(false), mReadOffset(0)
    {}

    File::File(const char* path, int flags)
        :mPath(path), mName(getFileName(path)), mEnding(getFileNameExtension(path)), mSource(0),mExist(checkExistFile(path)), mReadOffset(0)
    {
        if ((flags & FILE_CRT) == FILE_CRT)
        {
            if(!mExist)
            {
                ui64 lenRemove = mName.length() + mEnding.length() + 2;
                String dirPath(mPath);
                dirPath.remove(dirPath.length() - lenRemove, dirPath.length());
                createDirIfNotExist((const char *)dirPath.getSource());
                if(!(mExist = createFile(path)))
                {
                    LOG_ASSERT(false, {}, "Failed to create file with path: %s", path)
                }
            }
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

    }

    void File::read()
    {

    }

    void File::write()
    {

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

    ui64 File::capacity() const
    {
        mSource.capacity();
    }

    ui64 File::length() const
    {
        mSource.length();
    }

    bool File::exist() const
    {
        return mExist;
    }

    ui8* File::getData(size_t len)
    {

    }

    i8 File::getI8()
    {

    }

    ui8 File::getUI8()
    {

    }

    i16 File::getI16()
    {

    }

    ui16 File::getUI16()
    {

    }

    i32 File::getI32()
    {

    }

    [[maybe_unused]] ui32 File::getUI32()
    {

    }

    i64 File::getI64()
    {

    }

    ui64 File::getUI64()
    {

    }

    bool File::getBool()
    {

    }

    f32 File::getFloat()
    {

    }

    f64 File::getDouble()
    {

    }

    String File::getString()
    {

    }


    void File::addData(void* dat, ui64 len)
    {

    }

    void File::addI8(i8 dat)
    {
        mSource.add(dat);
    }

    void File::addUI8(ui8 dat)
    {
        mSource.add(dat);
    }

    void File::addI16(i16 dat)
    {
        mSource.add(dat);
    }

    void File::addUI16(ui16 dat)
    {
        mSource.add(dat);
    }

    void File::addI32(i32 dat)
    {
        mSource.add(dat);
    }

    void File::addUI32(ui32 dat)
    {
        mSource.add(dat);
    }

    void File::addI64(i64 dat)
    {
        mSource.add(dat);
    }

    void File::addUI64(ui64 dat)
    {
        mSource.add(dat);
    }

    void File::addBool(bool dat, bool asNum)
    {
        //mSource.add(dat, asNum);
    }

    void File::addF32(f32 dat)
    {
        mSource.add(dat);
    }

    void File::addF64(f64 dat)
    {
        mSource.add(dat);
    }

    void File::addString(const String& dat, bool withoutLen)
    {
        if(withoutLen)
        {
            mSource.add(dat);
            return;
        }

        mSource.add(dat.length());
        mSource.add(dat);
    }

    void File::addString(const std::string& dat, bool withoutLen)
    {
        if(withoutLen)
        {
            mSource.add(dat);
            return;
        }

        mSource.add(dat.size());
        mSource.add(dat);
    }

    void File::addString(const char* dat, bool withoutLen)
    {
        if(withoutLen)
        {
            mSource.add(dat);
            return;
        }

        mSource.add(strlen(dat));
        mSource.add(dat);
    }
}