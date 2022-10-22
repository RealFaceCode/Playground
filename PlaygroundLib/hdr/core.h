#ifndef CORE_H
#define CORE_H

#if !defined(NDEBUG)
#define _DEBUG
#endif

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

//GLM INCLUDES
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

//STD INCLUDES
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdarg>
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
void CoreInit();

std::string GetTime();
std::string GetDate();
std::string GetFileName(const char* fileName);
bool EndsWith(const char* filepath, const char* ending);

//C STRING HELPER
int vasprintf(char** strp, const char* fmt, va_list ap);
int asprintf(char **strp, const char *fmt, ...);

#endif // !CORE_H