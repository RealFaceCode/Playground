//
// Created by Kevin-Laptop on 10.08.2022.
//

//TODO: implement selection of multiple founds
#include "core.h"

#ifndef PLAYGROUNDLIB_LOGGER_H
#define PLAYGROUNDLIB_LOGGER_H

//DEFINES
#define ANSI_END "\033[m"

//ENUMS
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
struct Highlight
{
public:
    char* mToHighlight;
    char* mPrevColor;
    char* mHighlightColor;
};

//FUNCTIONS
const char* GetAnsiColor(const ConsoleOutPutColor& color);

Highlight CreateHighlighter(const char* toHighlight, const ConsoleOutPutColor& color);
void Highlighter(std::string& text, Highlight& highlight);

void Print(const char* format, ...);
void Print(const char* format, std::vector<Highlight>& highlights, ...);

void Log(const char* type,
         const ConsoleOutPutColor& logColor,
         const char* filePath, int line,
         std::vector<Highlight> highlights,
         const char* format,
         ...);

//FUNCTIONAL DEFINES
#ifdef _DEBUG
    #define C_HiLi(toHighlight, color) CreateHighlighter(toHighlight, color)
    #define LOG_INFO(highlights, fmt, ...)              { Log("INFO", LightGreen, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); }
    #define LOG_WARNING(highlights, fmt, ...)           { Log("WARNING", Orange, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); }
    #define LOG_ERROR(highlights, fmt, ...)             { Log("ERROR", Red, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); }
    #define LOG_ASSERT(boolean, highlights, fmt, ...)   { Log("ASSERT", LightPurple, __FILE__, __LINE__, highlights, fmt, ##__VA_ARGS__); assert(boolean); }
#else
    #define C_HiLi(toHighlight, color)
    #define LOG_INFO(highlights, fmt, ...)
    #define LOG_WARNING(highlights, fmt, ...)
    #define LOG_ERROR(highlights, fmt, ...)
    #define LOG_ASSERT(boolean, highlights, fmt, ...)
#endif
#endif //PLAYGROUNDLIB_LOGGER_H