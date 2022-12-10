#ifndef PLAYGROUNDLIB_FILESTREAM_H
#define PLAYGROUNDLIB_FILESTREAM_H

#include <../../hdr/core.h>
#include "buffer/string.h"
#include "buffer/binarybuffer.h"

namespace FS
{
    /**@brief Creates a file in the given path
     * @param[in] path
     * @retval TRUE     if the file successfully created
     * @retval FALSE    if the file is not successfully created
     */
    bool createFile(const char* path);
    /**@brief           Removes a file in the given path
     * @param[in] path
     * @retval TRUE     if the file successfully removed
     * @retval FALSE    if the file is not successfully removed
     */
    bool removeFile(const char* path);
    /**@brief Checks for a file existence
     * @param[in] path
     * @retval TRUE     if the file exist
     * @retval FALSE    if the dont file exist
    */
    bool checkExistFile(const char* path);
    /**@brief Renames a file
     * @param[in] path
     * @param[in] newName
     * @retval TRUE     if the file is successfully renamed
     * @retval FALSE    if the file is not successfully renamed
    */
    bool renameFile(const char* path, const char* newName);
    /**@brief Gets the actual size of the file.
     * @input CONST CHAR* the path of the file.
     * @returns
     * 0 if the file dont exist or the file has size 0. A size if the file exist
    */
    ui64 getFileSize(const char* path);
    /**@brief Creates a directory.
     * @param[in] dirPath
     * @retval TRUE     if the directory is successfully created.
     * @retval FALSE    if the directory is not successfully created.
    */
    bool createDir(const char* dirPath);
    /**@brief Removes a directory
     * @param[in] dirPath
     * @retval TRUE if the directory is successfully removed
     * @retval FALSE if the directory is not successfully removed
     */
    bool removeDir(const char* dirPath);
    /**@brief Checks if a directory exist
     * @param[in] dirPath
     * @retval TRUE if the directory exist
     * @retval FALSE if the directory dont exist
     */
    bool checkExistDir(const char* dirPath);
    /**@brief Creates directories if they dont exist
     * @param[in] dir
     * @returns
     * VOID
     */
    void createDirIfNotExist(const char* dir);
    /**@brief Checks if the directory has files
     * @param[in] dir
     * @retval TRUE if files in the directory
     * @retval FALSE if the directory empty
     */
    bool checkIfDirContainsFiles(const char* dir);
    /**@brief Gets the amount of file in the directory
    * @param[in] dir
    * @returns
     * 0 if no files exist, the path is not found or the path is a nullptr. a amount bigger than 0 if files exist in the directory
    */
    ui64 getFileCountFromDir(const char* dir);
    /**@brief Creates a Filename from the given file path.
    * @param[in] filePath
    * @returns
    * A String with the file name
    */
    String getFileName(const char* filePath);
    /**@brief Creates a file extension from the given file path.
    * @param[in] filePath
    * @returns
    * A String with the file extension
    */
    String getFileNameExtension(const char* filePath);
    /**@brief Gets all file names from a given directory
    * @param[in] dir
    * @returns
    * a std::vector<String> with all file names from a directory
    */
    std::vector<String> getFileNamesFromDir(const char* dir);
    /**@brief Gets all paths from a given directory
    * @param[in] dir
    * @returns
     * A std::vector<String> with all file path in the directory
    */
    std::vector<String> getFilePathsFromDir(const char* dir);
    /**@brief Writes to a file
     * @param[in] data
     * @param[in] filePath
     * @retval TRUE if the write was successful
     * @retval FALSE if the write was not successful
     */
    bool WriteToFile(const void* data, const ui64& bufLen, const char* filePath);
    /**@brief Reads from a file
     * @param[out] data
     * @param[in] bufLen
     * @param[in] filePath
     * @retval TRUE if the read was successful
     * @retval FALSE if the read was not successful
     */
    bool ReadFromFile(void** data, const char* filePath, const bool& nullTerm = false);

    /**@brief A buffer to store data and write it to a file or read from a file*/
    struct File
    {
        /**@brief Empty constructor. Initialized all values with 0*/
        File();
        /**@brief Initialized the struct based on the path and the flags
        * @param[in] path
        * @param[in] flags
        */
        File(const char* path, int flags = 0);
        /**@brief Deconstruct the class*/
        ~File();

        /**@brief Read the file with the given file path
        * @returns
        * VOID
        */
        void read();
        /**@brief Writes the data buffer to a file
        * @returns
        * VOID
        */
        void write();

        /**@brief Initialized the struct based on the path and the flags
        * @returns
        * A const String& to the path of the file
        */
        const String& getPath() const;
        /**@brief Gets the name of the file
         * @returns
         * A const String& to the name of the file
         */
        const String& getName() const;
        /**@brief Gets the file Extension of the file
         * @returns
         * A const String& to the file extension of the file
         */
        const String& getFileEnding() const;
        /**@brief Gets the actual data of the file
         * @returns
         * A BinaryBuffer&
         */
        BinaryBuffer& getData();
        /**@brief Gets the capacity of the data buffer
         * @returns
         * The actual capacity of the data buffer as a ui64
         */
        const ui64& capacity() const;
        /**@brief Gets the length of the data buffer
         * @returns
         * The actual length of the data buffer as a ui64
         */
        const ui64& length() const;
        /**@brief Checks if the file with the given path exist
        * @retval TRUE  if the file exist
        * @retval FALSE if the file dont exist
        */
        bool exist() const;

        /**@brief Gets data from the data buffer
        * @param[in] len
        * @returns
        * a ui8* for a given length of bytes
        */
        ui8* getData(const ui64& len);
        /**@brief Gets a i8
        * @returns
        * Returns a i8 from the data buffer
        */
        i8 getI8();
        /**@brief Gets a ui8
         * @returns
         * Returns a ui8 from the data buffer
         */
        ui8 getUI8();
        /**@brief Gets a i16
         * @returns
         * Returns a i16 from the data buffer
         */
        i16 getI16();
        /**@brief Gets a ui16
        * @returns
        * Returns a ui16 from the data buffer
        */
        ui16 getUI16();
        /**@brief Gets a i32
         * @returns
         * Returns a i32 from the data buffer
         */
        i32 getI32();
        /**@brief Gets a ui32
        * @returns
        * Returns a iui32from the data buffer
        */
        ui32 getUI32();
        /**@brief Gets a i64
         * @returns
         * Returns a i64 from the data buffer
         */
        i64 getI64();
        /**@brief Gets a ui64
         * @returns
         * Returns a ui64 from the data buffer
         */
        ui64 getUI64();
        /**@brief Gets a bool
         * @returns
         * Returns a bool from the data buffer
         */
        bool getBool();
        /**@brief Gets a f32
         * @returns
         * Returns a f32 from the data buffer
         */
        f32 getFloat();
        /**@brief Gets a f64
         * @returns
         * Returns a f64 from the data buffer
         */
        f64 getDouble();
        /**@brief Gets a String
         * @param[in] withoutLen
         * @returns
         * Returns a String from the data buffer
         */
        String getString(const bool& withoutLen = false);

        /**@brief Adds data with a given length to the data buffer
         * @param[in] dat
         * @param[in] len
         * @returns
         * VOID
         */
        void addData(void* dat, const ui64& len);
        /**@brief Adds a i8 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addI8(const i8& dat);
        /**@brief Adds a ui8 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addUI8(const ui8& dat);
        /**@brief Adds a i16 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addI16(const i16& dat);
        /**@brief Adds a ui16 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addUI16(const ui16& dat);
        /**@brief Adds a i32 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addI32(const i32& dat);
        /**@brief Adds a ui32 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addUI32(const ui32& dat);
        /**@brief Adds a i64 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addI64(const i64& dat);
        /**@brief Adds a ui64 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addUI64(const ui64& dat);
        /**@brief Adds a bool to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addBool(const bool& dat);
        /**@brief Adds a f32 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addF32(const f32& dat);
        /**@brief Adds a f43 to the data buffer
         * @param[in] dat
         * @returns
         * VOID
         */
        void addF64(const f64& dat);
        /**@brief Adds a String to the data buffer with or without the string length
         * @param[in] dat
         * @param[in] withoutLen
         * @returns
         * VOID
         */
        void addString(const String& dat, const bool& withoutLen = true);
        /**@brief Adds a std::string to the data buffer with or without the string length
         * @param[in] dat
         * @param[in] withoutLen
         * @returns
         * VOID
         */
        void addString(const std::string& dat, const bool& withoutLen = true);
        /**@brief Adds a c style string to the data buffer with or without the string length
         * @param[in] dat
         * @param[in] withoutLen
         * @returns
         * VOID
         */
        void addString(const char* dat, const bool& withoutLen = false);

    private:
        void createDirsAndFile();
    private:
        String mPath;
        String mName;
        String mEnding;
        BinaryBuffer mSource;
        bool mExist;
    };
}
#endif //PLAYGROUNDLIB_FILESTREAM_H