//
// Created by Kevin-Laptop on 18.08.2022.
//
#include "../../hdr/util/memory.h"
#include "../../hdr/core.h"
#include "../../hdr/logger.h"

constexpr int preReservedSpace = 1000;

struct MemoryTrace
{
public:
    void* mPtr;
    int mLine;
    char* mFile;
};

static bool trackMemory = false;

static std::vector<MemoryTrace> stackTrace;

void    MemoryEnableTracking(const bool& track)
{
    trackMemory = track;
    stackTrace.reserve(preReservedSpace);
}

void*   MemoryMalloc(size_t bytes, const char* file, const int& line)
{
    void* rPtr = malloc(bytes);
    if(trackMemory)
    {
        MemoryTrace mt{
            .mPtr = rPtr,
            .mLine = line,
            .mFile = const_cast<char*>(file),
        };
        stackTrace.emplace_back(mt);
    }

    return rPtr;
}

void*   MemoryRealloc(void* buffer, size_t bytes, const char* file, const int& line)
{
    void* rPtr = realloc(buffer, bytes);
    if(trackMemory)
    {
        for(auto& trace : stackTrace)
        {
            if(trace.mPtr == buffer)
            {
                trace.mPtr = rPtr;
                trace.mLine = line;
                trace.mFile = const_cast<char*>(file);
            }
        }
    }
    return rPtr;
}

void*   MemoryRegister(void* buffer, const char* file, const int& line)
{
    if(trackMemory)
    {
        for(const auto trace : stackTrace)
        {
            if(trace.mPtr == buffer)
            {
                return buffer;
            }
        }

        MemoryTrace mt{
            .mPtr = buffer,
            .mLine = line,
            .mFile = const_cast<char*>(file),
        };
        stackTrace.emplace_back(mt);
    }
    return buffer;
}

void*   MemoryDeRegister(void* buffer)
{
    if(trackMemory)
    {
        for(auto i = 0; i < stackTrace.size(); i++)
        {
            if(stackTrace.at(i).mPtr == buffer)
            {
                stackTrace.erase(stackTrace.begin() + i);
                break;
            }
        }
    }
    return buffer;
}

void    MemoryZero(void* buffer, size_t bytes)
{
    memset(buffer, 0, bytes);
}

void    MemoryFree(void* buffer)
{
    free(MemoryDeRegister(buffer));
}

void    MemoryPrintStack()
{
    if(stackTrace.empty())
    {
        return;
    }

    std::string leaks;
    for(const auto& trace : stackTrace)
    {
        std::string fmt("Memory leak detected at address: '%p' in file: '%s' at line %i\n");
        Highlight h = CreateHighlighter("%p", Yellow);
        Highlighter(fmt, h);
        h = CreateHighlighter("%s", Yellow);
        Highlighter(fmt, h);
        h = CreateHighlighter("%i", Yellow);
        Highlighter(fmt, h);
        leaks.append(GetFormatedString(fmt.c_str(),
                                       trace.mPtr, GetFileName(trace.mFile).c_str(), trace.mLine));
    }
    LOG_WARNING({}, leaks.c_str());
}