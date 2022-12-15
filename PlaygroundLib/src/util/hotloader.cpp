#include "../../hdr/core.h"
#include "../../hdr/logger.h"
#include "../../hdr/util/hotloader.h"
#include "../../hdr/util/buffer/string.h"
#include <sys/stat.h>

namespace HotLoader
{
    static std::map<String, FileWatch> watchedFiles;

    static time_t GetLastModifiedTime(const char* filePath)
    {
        if(!FHandle::checkExistFile(filePath))
        {
            return 0;
        }

        struct stat buf {};
        stat(filePath, &buf);
        return buf.st_mtime;
    }

    void AddFileToWatch(const char* filePath)
    {
        if(filePath == nullptr)
        {
            LOG_WARNING({}, "Failed to add file to file watcher! file path was nullptr!");
            return;
        }

        if(!FHandle::checkExistFile(filePath))
        {
            LOG_WARNING({}, "Failed to add file to file watcher with path'%s'! File do not exist!", filePath);
            return;
        }

        for(const auto& fileWatch : watchedFiles)
        {
            if(String(fileWatch.second.mFile.path) == String(filePath))
            {
                LOG_WARNING({}, "Failed to add file to watch with path'%s'!, File is already watched", filePath);
                return;
            }
        }

        watchedFiles.emplace(
                String(filePath),
                FileWatch
                {
                    .mFile = FHandle::File(filePath),
                    .mCheckTime = GetLastModifiedTime(filePath),
                    .mChanged = false
                }
            );
    }

    void RemoveFileToWatch(const char *filePath)
    {
        if (filePath == nullptr)
        {
            LOG_WARNING({}, "Failed to remove file watcher! file path was nullptr!");
            return;
        }

        if (watchedFiles.find(filePath) != watchedFiles.end()) {
            watchedFiles.erase(filePath);
        }
    }

    bool IsModified(const char *filePath) {

        for(const auto& fileWatch : watchedFiles)
        {
            if(fileWatch.first == String(filePath))
            {
                return fileWatch.second.mChanged;
            }
        }
        LOG_WARNING({}, "No file watch with path'%s'", filePath);
        return false;
    }

    FHandle::File *GetFile(const char *filePath)
    {
        for(auto& fileWatch : watchedFiles)
        {
            if(fileWatch.first == String(filePath))
            {
                fileWatch.second.mChanged = false;
                return &fileWatch.second.mFile;
            }
        }
        LOG_WARNING({}, "No file watch with path'%s'", filePath);
        return nullptr;
    }

    void CheckFiles()
    {
        for(auto& fileWatch : watchedFiles)
        {
            if(fileWatch.second.mCheckTime != GetLastModifiedTime(fileWatch.first.c_str()))
            {
                LOG_INFO({}, "Detected modified file with path'%s'", fileWatch.first.c_str());
                FHandle::File* file = &fileWatch.second.mFile;
                if(file->data == nullptr)
                {
                    delete file->data;
                    file->data = nullptr;
                }
                file->read();
                fileWatch.second.mCheckTime = GetLastModifiedTime(fileWatch.first.c_str());
                fileWatch.second.mChanged = true;
            }
        }
    }

    void Cleanup()
    {
        for(auto& p : watchedFiles)
        {
            auto& ref = (String&)p.first;
            ref.destroy();
        }
    }
}