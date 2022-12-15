#ifndef PLAYGROUNDLIB_FILELOGGER_H
#define PLAYGROUNDLIB_FILELOGGER_H
#include "util/buffer/string.h"

/**@brief Writes a log to a file
* @param[in] type
* @param[in] fileWritePath
* @param[in] filePath
* @param[in] line
* @param[in] format
* @param[in] ARGS
* @returns
* VOID
*/
void FileLog(const String& type,
             const String& fileWritePath,
             const String& filePath,
             const int& line,
             const String& format,
             ...);

/**@brief Cleans all related FileLog functions
     * @returns
     * VOID
     * @note This function should not be called. Its called automatically
     */
void FileLogCleanup();

#ifdef _DEBUG
    /**@brief Write a log to a file
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_INFO_FILE(filePath, fmt, ...)               { FileLog("INFO", filePath, __FILE__, __LINE__, fmt, ##__VA_ARGS__); }
    /**@brief Write a log to a file
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_WARNING_FILE(filePath, fmt, ...)            { FileLog("WARNING", filePath, __FILE__, __LINE__, fmt, ##__VA_ARGS__); }
    /**@brief Write a log to a file
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ERROR_FILE(filePath, fmt, ...)              { FileLog("ERROR", filePath, __FILE__, __LINE__, fmt, ##__VA_ARGS__); }
    /**@brief Write a log to a file
     * @param boolean
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ASSERT_FILE(boolean, filePath, fmt, ...)    { FileLog("ASSERT", filePath, __FILE__, __LINE__, fmt, ##__VA_ARGS__); assert(boolean); }
#else
    /**@brief Write a log to a file
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_INFO_FILE(filepath, fmt, ...)
    /**@brief Write a log to a file
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_WARNING_FILE(filepath, fmt, ...)
    /**@brief Write a log to a file
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ERROR_FILE(filepath, fmt, ...)
    /**@brief Write a log to a file
     * @param boolean
     * @param[in] filePath
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ASSERT_FILE(boolean, filepath, fmt, ...)
#endif
#endif //PLAYGROUNDLIB_FILELOGGER_H