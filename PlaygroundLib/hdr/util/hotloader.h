//
// Created by Kevin-Laptop on 07.08.2022.
//

#ifndef PLAYGROUNDLIB_HOTLOADER_H
#define PLAYGROUNDLIB_HOTLOADER_H

namespace HotLoader
{
    /**@brief Holds all information to watch if a file was changed*/
    struct FileWatch
    {
        FHandle::File mFile;
        time_t mCheckTime;
        bool mChanged;
    };

    /**@brief Adds a new file to the file watch list
     * @param[in] filePath
     * @returns
     * VOID
     */
    void AddFileToWatch(const char* filePath);
    /**@brief Removes a file from the file watch list
     * @param[in] filePath
     * @returns
     * VOID
     */
    void RemoveFileToWatch(const char* filePath);
    /**@brief Checks if a file in the watch list was modified
     * @param[in] filePath
     * @retval TRUE     if the file is modified
     * @retval FALSE    if the file is not modified
     */
    bool IsModified(const char* filePath);
    /**@brief Gets the modified file by file path
     * @param[in] filePath
     * @returns
     * A FS::File* to the modified file
     */
    FHandle::File* GetFile(const char* filePath);
    /**@brief Checks all files for modification
     * @returns
     * VOID
     */
    void CheckFiles();
}
#endif //PLAYGROUNDLIB_HOTLOADER_H