//
// Created by Kevin-Laptop on 10.08.2022.
//

#include "../hdr/core.h"
#include "../hdr/logger.h"
#include "../hdr/util/memory.h"

const char* GetAnsiColor(const ConsoleOutPutColor& color)
{
    switch (color)
    {
        case LightGreen:    return "\033[38;5;46m";
        case Green:         return "\033[38;5;34m";
        case DarkGreen:     return "\033[38;5;22m";
        case Yellow:        return "\033[38;5;226m";
        case Orange:        return "\033[38;5;202m";
        case LightRed:      return "\033[38;5;9m";
        case Red:           return "\033[38;5;196m";
        case DarkRed:       return "\033[38;5;88m";
        case LightPurple:   return "\033[38;5;177m";
        case Purple:        return "\033[38;5;201m";
        case DarkPurple:    return "\033[38;5;165m";
        case LightBlue:     return "\033[38;5;12m";
        case Blue:          return "\033[38;5;21m";
        case Darkblue:      return "\033[38;5;18m";
        case LightGray:     return "\033[38;5;247m";
        case Gray:          return "\033[38;5;242m";
        case DarkGray:      return "\033[38;5;236m";
    }
    return "\033[38;5;236m";
}

Highlight CreateHighlighter(const char* toHighlight, const ConsoleOutPutColor& color)
{
    return {
        .mToHighlight = (char*)toHighlight,
        .mPrevColor = (char*)ANSI_END,
        .mHighlightColor = (char*)GetAnsiColor(color),
    };
}

void Highlighter(std::string& text, Highlight& highlight)
{
    auto pos = text.find(highlight.mToHighlight);
    text.insert(pos, highlight.mHighlightColor);
    pos = text.find(highlight.mToHighlight) + strlen(highlight.mToHighlight);
    text.insert(pos, highlight.mPrevColor);
}

void Log(const char* type,
         const ConsoleOutPutColor& logColor,
         const char* filePath,
         int line,
         std::vector<Highlight> highlights,
         const char* format,
         ...)
{
    std::string userFormat(format);

    for(auto i = 0; i < highlights.size(); i++)
    {
        if(i != 0)
        {
            highlights.at(i).mPrevColor = highlights.at(i - 1).mHighlightColor;
        }
        Highlighter(userFormat, highlights.at(i));
    }

    char* str;
    va_list args;
    va_start(args, userFormat.data());
    //Allocates dynamically memory for str. str hax to be freed later
    vasprintf(&str, userFormat.data(), args);
    va_end(args);

    userFormat.clear();
    userFormat.append(str);

    Free(str);

    const char* color       = GetAnsiColor(logColor);
    const auto fName        = GetFileName(filePath);
    const auto date         = GetDate();
    const auto time         = GetTime();
    const char* fileName    = fName.c_str();
    const char* cDate       = date.c_str();
    const char* cTime       = time.c_str();

    //Allocates dynamically memory for str. str hax to be freed later
    asprintf(&str,
             "%s[%s][FILE:%s][LINE:%i][%s][%s]%s",
             color, type,fileName,line, cDate, cTime, ANSI_END);

    printf("%s\n%s\n", str, userFormat.c_str());
    Free(str);
}