#ifndef CORE_H
#define CORE_H

#ifndef DEFINE_CORE_DEFINES
#define DEFINE_CORE_DEFINES
	#define _CRT_SECURE_NO_WARNINGS
	#define STB_IMAGE_WRITE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#ifdef WIN32
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #define DISABLE_NEWLINE_AUTO_RETURN  0x0008
    #include <windows.h>
    #define PREP_CONSOLE_LOG { \
        HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);\
        DWORD consoleMode;\
        GetConsoleMode( handleOut , &consoleMode);\
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;\
        consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;\
        SetConsoleMode( handleOut , consoleMode );\
    };
#else
    #define PREP_CONSOLE_LOG
#endif

//GLFW INCLUDES
#include <GLFW/glfw3.h>

//GLAD INCLUDES
#include <glad/glad.h>

//GLM INCLUDES
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

//STBI INCLUDES

//IMGUI INCLUDES

//PROFILING INCLUDES

//ASSIMP INCLUDES

//TASKFLOW INCLUDES

//MESHOPTIMIZER INCLUDES

//STD INCLUDES
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <stdarg.h>
#include <chrono>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <memory>

//FILEHANDLE
#include <BasicFileHandling.h>
#include <File.h>
#include <Node.h>

//TYPEDEFS
typedef int8_t		i8;
typedef uint8_t		ui8;
typedef int16_t		i16;
typedef uint16_t	ui16;
typedef int32_t		i32;
typedef uint32_t	ui32;
typedef int64_t		i64;
typedef uint64_t	ui64;
typedef float		f32;
typedef double		f64;

//ENUMS

//Structs
template<typename T>
struct Result
{
public:
    T type;
    bool result;

public:
    T unwrap();

public:
    explicit operator bool() const noexcept;
};

template<typename T>
T Result<T>::unwrap() {
    return type;
}

template<typename T>
Result<T>::operator bool() const noexcept {
    return result;
}

//FUNCTIONS
std::string GetTime();
std::string GetDate();
std::string GetFileName(const char* fileName);
std::string GetFormatedString(const char* fmt, ...);
std::string ToString(const char* str);
std::string ToString(std::string str);
std::string ToString(int i);
std::string ToString(unsigned int ui);
std::string ToString(float f);
std::string ToString(double d);
bool EndsWith(const char* filepath, const char* ending);

//C STRING HELPER
int vasprintf(char** strp, const char* fmt, va_list ap);

static const char* LogPath_				= "log.txt";
static FILE* LogFile_					= fopen(LogPath_, "a");

#define LOG_COLOR_BLUE					"\x1B[34m"
#define LOG_COLOR_GREEN					"\x1B[32m"
#define LOG_COLOR_YELLOW				"\x1B[33m"
#define LOG_COLOR_RED					"\x1B[31m"
#define LOG_COLOR_PURPLE				"\x1B[35m"

#define LOG_COLOR_FMT_FULL				"%s[%s][FILE:%s][LINE:%i][%s][%s]\n%s\n\033[0m"
#define LOG_COLOR_FMT					"%s[%s][FILE:%s][LINE:%i][%s][%s]\033[0m\n%s\n"
#define LOG_COLOR_FMT_FULL_WITHOUT_DATE	"%s[%s][FILE:%s][LINE:%i][%s][%s]\n%s\n\033[0m"
#define LOG_COLOR_FMT_WITHOUT_DATE		"%s[%s][FILE:%s][LINE:%i][%s][%s]\033[0m\n%s\n"
#define LOG_TO_FILE_FMT					"[%s][FILE:%s][LINE:%i][%s][%s]\n%s\n"

#define log_to_file(msg) {\
	if(!LogFile_)\
	{\
		assert(false);\
	}\
	fwrite(msg, 1, sizeof(char) * strlen(msg), LogFile_);\
	fflush(LogFile_);\
}

#ifdef LOG_TO_FILE
	#define log_and_write(color, type, fmt, msg) {\
		std::string outC = GetFormatedString(fmt, color, type, GetFileName(__FILE__).c_str(), __LINE__, GetTime().c_str(), GetDate().c_str(), msg);\
		printf(outC.c_str());\
		std::string outF = GetFormatedString(LOG_TO_FILE_FMT, type, GetFileName(__FILE__).c_str(), __LINE__, GetTime().c_str(), GetDate().c_str(), msg);\
		log_to_file(outF.c_str());\
	    _flushall();\
	}
#else
	#define log_and_write(color, type, fmt, msg) {\
		std::string outC = GetFormatedString(fmt, color, type, GetFileName(__FILE__).c_str(), __LINE__, GetTime().c_str(), GetDate().c_str(), msg);\
		printf(outC.c_str());\
	    _flushall();\
	}
#endif // LOG_TO_FILE

#ifdef LOG_COLOR_FULL
	#define log_(color, type, msg)		log_and_write(color, type, LOG_COLOR_FMT_FULL, ToString(msg).c_str());
#else
	#define log_(color, type, msg)		log_and_write(color, type, LOG_COLOR_FMT, ToString(msg).c_str());
#endif // LOG_FULL_COLOR

#ifdef _DEBUG
	#define log_msg(msg)					log_(LOG_COLOR_BLUE, "MSG", msg);
	#define log_info(msg)					log_(LOG_COLOR_GREEN,"INFO", msg);
	#define log_warning(msg)				log_(LOG_COLOR_YELLOW, "WARNING", msg);
	#define log_error(msg)					log_(LOG_COLOR_RED, "ERROR", msg);
	#define log_assert(boolean, msg)		log_(LOG_COLOR_PURPLE, "ASSERT", msg); assert(boolean);
	#define log_fmt_msg(fmt, ...)			log_(LOG_COLOR_BLUE, "MSG", GetFormatedString(fmt, __VA_ARGS__));
	#define log_fmt_info(fmt, ...)			log_(LOG_COLOR_GREEN,"INFO", GetFormatedString(fmt, __VA_ARGS__));
	#define log_fmt_warning(fmt,...)		log_(LOG_COLOR_YELLOW, "WARNING", GetFormatedString(fmt, __VA_ARGS__));
	#define log_fmt_error(fmt, ...)			log_(LOG_COLOR_RED, "ERROR", GetFormatedString(fmt, __VA_ARGS__));
	#define log_fmt_assert(boolean,fmt,...)	log_(LOG_COLOR_PURPLE, "ASSERT", GetFormatedString(fmt, __VA_ARGS__)); assert(boolean);
#else
	#define log_msg(msg)
	#define log_info(msg)
	#define log_warning(msg)
	#define log_error(msg)
	#define log_assert(boolean, msg)		assert(boolean);
	#define log_fmt_msg(fmt,...)
	#define log_fmt_info(fmt,...)
	#define log_fmt_warning(fmt, ...)
	#define log_fmt_error(fmt, ...)
	#define log_fmt_assert(boolean,fmt,...)	assert(boolean);
#endif // DEBUG
#endif // !CORE_H