#pragma once
#include <cstdint>

namespace FHandle 
{
#define FILE_CRT							0x00000001
#define FILE_CLR							0x00000010
#define FILE_GET_SIZE						0x00000100
#define FILE_CHECK_EXIST					0x00001000
#define FILE_READ							0x00010000

	class File {
	public:
		char* path;
		uint64_t	lenTotal;
		uint64_t	lenData;
		uint64_t	lenRead;
		bool		fileExist;
		uint8_t*	data;
		char*		fileName;
		char*		fileEnding;

	public:
		File() = default;
		~File();
		// Creates File struct
		// Standard flags = 0
		File(const char* path, int flags = 0);
		File(const File& file);

		const char* getPath();
		char* getName();
		char* getFileEnding();
		uint64_t size();
		uint64_t getDataLen();
		uint64_t getReadLen();
		bool exist();

		uint8_t* getData();
		uint8_t* getData(size_t len);
		int8_t getI8();
		uint8_t getUI8();
		int16_t getI16();
		uint16_t getUI16();
		int32_t getI32();
		uint32_t getUI32();
		int64_t getI64();
		uint64_t getUI64();
		bool getBool();
		float getFloat();
		double getDouble();
		char* getCString();

		void addData(void* dat, uint64_t len);
		void addI8(int8_t dat);
		void addUI8(uint8_t dat);
		void addI16(int16_t dat);
		void addUI16(uint16_t dat);
		void addI32(int32_t dat);
		void addUI32(uint32_t dat);
		void addI64(int64_t dat);
		void addUI64(uint64_t dat);
		void addBool(bool dat);
		void addFloat(float dat);
		void addDouble(double dat);
		void addStringWithoutLen(const char* dat);	//Adds a string without the string length
		void addString(const char* dat);			//Adds a string with the string length

		bool read();
		bool write();
		void clear();

		void reserve(size_t bytes);

		operator bool();
	};

	
}