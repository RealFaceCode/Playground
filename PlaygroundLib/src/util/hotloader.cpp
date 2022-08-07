//
// Created by Kevin-Laptop on 07.08.2022.
//

#include "../../hdr/core.h"
#include "../../hdr/util/hotloader.h"

namespace HotLoader
{
    static std::unordered_map<std::string, FileWatch> watchedFiles;

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

    //TODO: rewrite logging to file watcher instead of file to watch
    void AddFileToWatch(const char* filePath)
    {
        if(filePath == nullptr)
        {
            log_warning("Failed to add file to watch! file path was nullptr!");
            return;
        }

        if(!FHandle::checkExistFile(filePath))
        {
            log_fmt_warning("Failed to add file to watch with path'%s'! File do not exist!", filePath);
            return;
        }

        for(const auto& fileWatch : watchedFiles)
        {
            if(std::string(fileWatch.second.mFile.path) == std::string(filePath))
            {
                log_fmt_warning("Failed to add file to watch with path'%s'!, File is already watched", filePath);
                return;
            }
        }

        watchedFiles.emplace(
                std::string(filePath),
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
        if (filePath == nullptr) {
            log_warning("Failed to remove file watcher! file path was nullptr!");
            return;
        }

        if (watchedFiles.find(std::string(filePath)) != watchedFiles.end()) {
            watchedFiles.erase(std::string(filePath));
        }
    }

    bool IsModified(const char *filePath) {

        for(const auto& fileWatch : watchedFiles)
        {
            if(fileWatch.first == std::string(filePath))
            {
                return fileWatch.second.mChanged;
            }
        }
        log_fmt_warning("No file watch with path'%s'", filePath);
        return false;
    }

    FHandle::File *GetFile(const char *filePath)
    {
        for(auto& fileWatch : watchedFiles)
        {
            if(fileWatch.first == std::string(filePath))
            {
                fileWatch.second.mChanged = false;
                return &fileWatch.second.mFile;
            }
        }
        log_fmt_warning("No file watch with path'%s'", filePath);
        return nullptr;
    }

    void CheckFiles()
    {
        for(auto& fileWatch : watchedFiles)
        {
            if(fileWatch.second.mCheckTime != GetLastModifiedTime(fileWatch.first.c_str()))
            {
                log_fmt_info("Detected modified file with path'%s'", fileWatch.first.c_str());
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
}