#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace FHandle
{
	bool createFile(const char* path);								// Creates a file, return false if path == nullptr or file already exist
	bool removeFile(const char* path);								// Removes a file, return false if path == nullptr or no file exist
	bool checkExistFile(const char* path);							// Checking for a file, return false if no file exist ore path == nullptr
	bool renameFile(const char* path, const char* newName);			// Renames an existing file, return false if path ore newName == nullptr or no file exist or rename failed
	uint64_t getFileSize(const char* path);							// Return the filesize, return 0 if file has len 0 or no file exist or path == nullptr
	bool createDir(const char* dirPath);							// Creates a directory, returns 0 if the directory already exist or path == nullptr
	bool removeDir(const char* dirPath);							// Removes a directory, return false if no directory exist
	bool checkExistDir(const char* dirPath);						// Checks if a directory exist, return false if no exist
	void createDirIfNotExist(const char* dir);
	bool checkIfDirContainsFiles(const char* dir);
	uint64_t getFileCountFromDir(const char* dir);
	std::string getFileName(const char* filePath);
    std::string getFileNameExtension(const char* filePath);
	std::vector<std::string> getFileNamesFromDir(const char* dir);
	std::vector<std::string> getFilePathsFromDir(const char* dir);
}

