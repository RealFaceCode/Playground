#include "../../hdr/util/memory.h"
#include "../../hdr/core.h"
#include "../../hdr/logger.h"
#include "../../hdr/util/FileStream.h"

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

bool    MemoryPrintStack()
{
    if(stackTrace.empty())
    {
        return false;
    }

    std::string leaks;
    for(const auto& trace : stackTrace)
    {
        char* fmt = (char*)"Memory leak detected at address: '\033[38;5;226m%p\\033[m' in file: '\033[38;5;226m%s\\033[m' at line \033[38;5;226m%i\\033[m\n";
        char* str;
        asprintf(&str, fmt, trace.mPtr, FS::getFileName(trace.mFile).c_str(), trace.mLine);
        leaks.append(str);
        Free(str);
    }
    LOG_WARNING({}, leaks.c_str());
    return true;
}