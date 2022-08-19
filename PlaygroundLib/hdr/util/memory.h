//
// Created by Kevin-Laptop on 18.08.2022.
//

#ifndef PLAYGROUNDLIB_MEMORY_H
#define PLAYGROUNDLIB_MEMORY_H

void    MemoryEnableTracking(const bool& track);
void*   MemoryMalloc(size_t bytes, const char* file, const int& line);
void*   MemoryRealloc(void* buffer, size_t bytes, const char* file, const int& line);
void*   MemoryRegister(void* buffer, const char* file, const int& line);
void    MemoryZero(void* buffer, size_t bytes);
void    MemoryFree(void* buffer);
void    MemoryPrintStack();

#ifdef _DEBUG
    #define Malloc(bytes)           MemoryMalloc(bytes, __FILE__, __LINE__)
    #define Realloca(buffer, bytes) MemoryRealloc(buffer, bytes, __FILE__, __LINE__)
    #define Free(buffer)            MemoryFree(buffer)
    #define MemReg(buffer)          MemoryRegister(buffer, __FILE__, __LINE__)
#else
    #define Malloc(bytes)           malloc(bytes)
    #define Realloca(buffer, bytes) realloc(buffer, bytes)
    #define Free(buffer)            free(buffer)
    #define MemReg(buffer)          buffer
#endif

#define MemZero(buffer, bytes)  MemoryZero(buffer, bytes)

#endif //PLAYGROUNDLIB_MEMORY_H
