#ifndef PLAYGROUNDLIB_LOGGER_H
#define PLAYGROUNDLIB_LOGGER_H
#include "core.h"
#include "util/buffer/string.h"

//DEFINES
#define ANSI_END "\033[m"

//ENUMS
/**@brief Defines the supported colors for the console output*/
enum ConsoleOutPutColor : ui8
{
    LightGreen = 0,
    Green,
    DarkGreen,
    Yellow,
    Orange,
    LightRed,
    Red,
    DarkRed,
    LightPurple,
    Purple,
    DarkPurple,
    LightBlue,
    Blue,
    Darkblue,
    LightGray,
    Gray,
    DarkGray
};

//STRUCTS
/**@brief Holds all the information for a text highlight*/
struct Highlight
{
public:
    ui64 mIndex;
    String mToHighlight;
    String mPrevColor;
    String mHighlightColor;
};

//FUNCTIONS
/**@brief Converts the enum type color to a c style string representation
* @param[in] color
* @returns
* Returns a c style string representation of the given color from the enum type.
*/
String GetAnsiColor(const ConsoleOutPutColor& color);

/**@brief Creates a highlight for text highlighting
* @param[in] toHighlight
* @param[in] color
* @param[in] index
* @returns
* Returns a c style string representation of the given color from the enum type.
*/
Highlight CreateHighlighter(const String& toHighlight, const ConsoleOutPutColor& color, const ui64& index);
/**@brief Highlights the given string with the given highlight
* @param[in/out] toHighlight
* @param[in] color
* @returns
* VOID
*/
void Highlighter(String& text, Highlight& highlight);

/**@brief Prints a log to the console
* @param[in] type
* @param[in] logColor
* @param[in] filePath
* @param[in] line
* @param[in] highlights
* @param[in] format
* @param[in] ARGS
* @returns
* VOID
*/
void Log(const String& type,
         const ConsoleOutPutColor& logColor,
         const String& filePath, const int& line,
         std::vector<Highlight> highlights,
         const String& format,
         ...);

//FUNCTIONAL DEFINES
#ifdef _DEBUG
    /**@brief Creates a highlight for text highlighting
    * @param[in] toHighlight
    * @param[in] color
    * @param[in] index
    * @returns
    * Returns a c style string representation of the given color from the enum type.
    */
    #define C_HiLi(toHighlight, color, index)                  CreateHighlighter(toHighlight, color, index)
    /**@brief Prints a info log to the console
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_INFO(highlights, fmt, ...)              { Log("INFO", LightGreen, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); }
    /**@brief Prints a warning log to the console
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_WARNING(highlights, fmt, ...)           { Log("WARNING", Orange, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); }
    /**@brief Prints a error log to the console
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ERROR(highlights, fmt, ...)             { Log("ERROR", Red, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); }
    /**@brief Prints a assert log to the console and based on the boolean input it asserts the programm
     * @param[in] boolean
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ASSERT(boolean, highlights, fmt, ...)   { Log("ASSERT", LightPurple, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); assert(boolean); }
#else
    /**@brief Creates a highlight for text highlighting
    * @param[in] toHighlight
    * @param[in] color
    * @param[in] index
    * @returns
    * Returns a c style string representation of the given color from the enum type.
    */
    #define C_HiLi(toHighlight, color, index)
    /**@brief Prints a info log to the console
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_INFO(highlights, fmt, ...)
    /**@brief Prints a warning log to the console
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_WARNING(highlights, fmt, ...)
    /**@brief Prints a error log to the console
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ERROR(highlights, fmt, ...)
    /**@brief Prints a assert log to the console and based on the boolean input it asserts the programm
     * @param[in] boolean
     * @param[in] highlights
     * @param[in] fmt
     * @param[in] ARGS
     * @returns
     * VOID
     */
    #define LOG_ASSERT(boolean, highlights, fmt, ...)
#endif
#endif //PLAYGROUNDLIB_LOGGER_H