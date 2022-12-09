#ifndef PLAYGROUNDLIB_MEMORY_H
#define PLAYGROUNDLIB_MEMORY_H
#include <cstdint>

/**@brief Enables the tracking of heap allocated memory
 * @param[in] track
 * @returns
 * VOID
 */
void    MemoryEnableTracking(const bool& track);
/**@brief Allocates memory on the heap by a given size and adds the buffer for tracking if memory tracking is enabled
 * @param[in] bytes
 * @param[in] file
 * @param[in] line
 * @returns
 * Return a memory address if the memory allocation was successful and a nullptr if the memory allocation failed
 */
void*   MemoryMalloc(size_t bytes, const char* file, const int& line);
/**@brief Reallocates memory on the heap by a given size and adds the buffer for tracking if memory tracking is enabled
 * @param[in] buffer
 * @param[in] bytes
 * @param[in] file
 * @param[in] line
 * @returns
 * Return a memory address if the memory allocation was successful and a nullptr if the memory allocation failed
 */
void*   MemoryRealloc(void* buffer, size_t bytes, const char* file, const int& line);
/**@brief Adds a unknown pointer to track
 * @param[in] buffer
 * @param[in] file
 * @param[in] line
 * @retur
 * Returns the buffer given as input in field buffer
 */
void*   MemoryRegister(void* buffer, const char* file, const int& line);
/**@brief Removes a pointer from tracking if memory tracking is enabled
 * @param[in] buffer
 * @returns
 * returns the buffer given as input in field buffer
 */
void*   MemoryDeRegister(void* buffer);
/**@brief Sets the memory to the value 0 for a given length
 * @param[in] buffer
 * @param[in] bytes
 * @returns
 * VOID
 */
void    MemoryZero(void* buffer, size_t bytes);
/**@brief Frees the buffer and removes it from tracking
 * @param[in] buffer
 * @returns
 * VOID
 */
void    MemoryFree(void* buffer);
/**@brief Prints all memory leaks if memory tracking is enabled
 * @returns
 * VOID
 */
bool    MemoryPrintStack();

#ifdef _DEBUG
    /**@brief Allocates memory on the heap by a given size and adds the buffer for tracking if memory tracking is enabled
     * @param[in] buffer
     * @returns
     * Return a memory address if the memory allocation was successful and a nullptr if the memory allocation failed
     */
    #define Malloc(bytes)           MemoryMalloc(bytes, __FILE__, __LINE__)
    /**@brief Reallocates memory on the heap by a given size and adds the buffer for tracking if memory tracking is enabled
     * @param[in] buffer
     * @param[in] bytes
     * @returns
     * Return a memory address if the memory allocation was successful and a nullptr if the memory allocation failed
     */
    #define Realloc(buffer, bytes)  MemoryRealloc(buffer, bytes, __FILE__, __LINE__)
    /**@brief Frees the buffer and removes it from tracking
      * @param[in] buffer
      * @returns
      * VOID
      */
    #define Free(buffer)            MemoryFree(buffer)
    /**@brief Adds a unknown pointer to track
     * @param[in] buffer
     * @returns
     * Returns the buffer given as input in field buffer
     */
    #define MemReg(buffer)          MemoryRegister(buffer, __FILE__, __LINE__)
    /**@brief Removes a pointer from tracking if memory tracking is enabled
     * @param[in] buffer
     * @returns
     * returns the buffer given as input in field buffer
     */
    #define MemDeReg(buffer)        MemoryDeRegister(buffer)
#else
    /**@brief Allocates memory on the heap by a given size and adds the buffer for tracking if memory tracking is enabled
        * @param[in] buffer
        * @returns
        * Return a memory address if the memory allocation was successful and a nullptr if the memory allocation failed
        */
    #define Malloc(bytes)       malloc(bytes)
    /**@brief Reallocates memory on the heap by a given size and adds the buffer for tracking if memory tracking is enabled
     * @param[in] buffer
     * @param[in] bytes
     * @returns
     * Return a memory address if the memory allocation was successful and a nullptr if the memory allocation failed
     */
    #define Realloc(buffer, bytes)  realloc(buffer, bytes)
    /**@brief Frees the buffer and removes it from tracking
      * @param[in] buffer
      * @returns
      * VOID
      */
    #define Free(buffer)            free(buffer)
    /**@brief Adds a unknown pointer to track
     * @param[in] buffer
     * @returns
     * Returns the buffer given as input in field buffer
     */
    #define MemReg(buffer)          buffer
    /**@brief Removes a pointer from tracking if memory tracking is enabled
     * @param[in] buffer
     * @returns
     * returns the buffer given as input in field buffer
     */
    #define MemDeReg(buffer)        buffer
#endif

/**@brief Sets the memory to the value 0 for a given length
 * @param[in] buffer
 * @param[in] bytes
 * @returns
 * VOID
 */
#define MemZero(buffer, bytes)  MemoryZero(buffer, bytes)
#endif //PLAYGROUNDLIB_MEMORY_H