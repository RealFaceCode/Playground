#ifndef CORE_H
#define CORE_H
//TODO: rewrite

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
    /**@brief Prepares the console for colored text output*/
    #define PREP_CONSOLE_LOG { \
        HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);\
        DWORD consoleMode;\
        GetConsoleMode(handleOut, &consoleMode);\
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;\
        consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;\
        SetConsoleMode(handleOut, consoleMode );\
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
struct String;

/**@brief Class for checking results*/
template<typename T>
struct Result
{
public:
    T type;
    bool result;

public:
    /**@brief Unwraps the given value
         * @returns
         * Returns a given result with a given type
         */
    T unwrap();

public:
    /**@brief Checks if the result is valid
         * @returns
         * Returns if the result is valid or not based on the result
         */
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
/**@brief Initialized all core related functions
 * @returns
 * VOID
 */
void CoreInit();
/**@brief Cleans all core related functions
 * @returns
 * VOID
 * @note This function is called automatically. This should not called manually!
 */
void CoreCleanup();

/**@brief Gets the time as a String
 * @returns
 * Returns a String with the actual time
 */
String GetTime();
/**@brief Gets the date as a String
 * @returns
 * Returns a String with the actual date
 */
String GetDate();
/**@brief Checks if a file path end with a given file extension
 * @retval TRUE if the file ends with the file extension
 * @retval FALSE if the file dont ends with the file extension
 */
bool EndsWith(const String& filepath, const String& ending);

//C STRING HELPER
int vasprintf(char** strp, const char* fmt, va_list ap);
int asprintf(char **strp, const char *fmt, ...);

#endif // !CORE_H