//
// Created by Kevin-Laptop on 07.08.2022.
//

#ifndef PLAYGROUNDLIB_HOTLOADER_H
#define PLAYGROUNDLIB_HOTLOADER_H

namespace HotLoader
{
    struct FileWatch
    {
        FHandle::File mFile;
        time_t mCheckTime;
        bool mChanged;
    };

    void AddFileToWatch(const char* filePath);
    void RemoveFileToWatch(const char* filePath);
    bool IsModified(const char* filePath);
    FHandle::File* GetFile(const char* filePath);
    void CheckFiles();
}

#endif //PLAYGROUNDLIB_HOTLOADER_H