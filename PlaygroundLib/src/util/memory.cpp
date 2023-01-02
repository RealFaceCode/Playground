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
#ifdef _DEBUG
    trackMemory = track;
    stackTrace.reserve(preReservedSpace);
 #endif
}

void*   MemoryMalloc(size_t bytes, const char* file, const int& line)
{
    void* rPtr = malloc(bytes);
#ifdef _DEBUG
    if(trackMemory)
    {
        MemoryTrace mt{
            .mPtr = rPtr,
            .mLine = line,
            .mFile = const_cast<char*>(file),
        };
        stackTrace.emplace_back(mt);
    }
#endif
    MemoryZero(rPtr, bytes);
    return rPtr;
}

void*   MemoryRealloc(void* buffer, size_t bytes, const char* file, const int& line)
{
    void* rPtr = realloc(buffer, bytes);
#ifdef _DEBUG
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
#endif
    return rPtr;
}

void*   MemoryRealloc_s(void* buffer, size_t bytesBuffer, size_t bytesAdd, const char* file, const int& line)
{
    void* rPtr = MemoryRealloc(buffer, bytesBuffer + bytesAdd, file, line);
    MemoryZero((char*)rPtr + bytesBuffer, bytesAdd);
    return rPtr;
}

void*   MemoryRegister(void* buffer, const char* file, const int& line)
{
#ifdef _DEBUG
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
#endif
    return buffer;
}

void*   MemoryDeRegister(void* buffer)
{
#ifdef _DEBUG
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
#endif
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
#ifdef _DEBUG
    if(stackTrace.empty())
    {
        return false;
    }

    std::string leaks;
    for(const auto& trace : stackTrace)
    {
        char* fmt = (char*)"Memory leak detected at address: '\033[38;5;226m%p\033[m' in file: '\033[38;5;226m%s\033[m' at line \033[38;5;226m%i\033[m\n";
        char* str;
        asprintf(&str, fmt, trace.mPtr, FS::getFileName(trace.mFile).c_str(), trace.mLine);
        leaks.append(str);
        MemoryFree(str);
    }
    LOG_WARNING({}, leaks.c_str());
#endif
    return true;
}