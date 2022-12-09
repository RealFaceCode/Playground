#ifndef PLAYGROUNDLIB_BINARYBUFFER_H
#define PLAYGROUNDLIB_BINARYBUFFER_H
#include "../../core.h"
#include "string.h"

struct BinaryBuffer
{
public:
    /**@brief Empty constructor for a BinaryBuffer. All values are set to 0*/
    BinaryBuffer();
    /**@brief Creates a empty BinaryBuffer with a given length in bytes
    * @param[in] bufferLen
    */
    BinaryBuffer(const ui64& bufferLen);
    /**@brief Deconstructs the BinaryBuffer and sets all values to 0
    */
    ~BinaryBuffer();

    /**@brief Pushes new data at the end of the buffer, is the buffer to small new space will be automatically allocated
    * @param[in] size
    * @param[in] data
    * @returns
    * VOID
    */
    void push(const ui64& size, void* data);
    /**@brief Pops data as a void* for a given size in bytes
    * @param[in] size
    * @returns
    * Returns a void* with a given length. To get the actual data it should be casted to a type pointer and dereference it.
    * The pointer should not be freed!
    * @code int result = *(int*) pop(8);
    */
    void* pop(const ui64& size);

    /**@brief Adds a i8 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const i8& integer);
    /**@brief Adds a i16 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const i16& integer);
    /**@brief Adds a i32 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const i32& integer);
    /**@brief Adds a i64 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const i64& integer);
    /**@brief Adds a ui8 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const ui8& integer);
    /**@brief Adds a ui16 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const ui16& integer);
    /**@brief Adds a ui32 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const ui32& integer);
    /**@brief Adds a ui64 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] integer
    * @returns
    * VOID
    */
    void add(const ui64& integer);
    /**@brief Adds a f32 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] f
    * @returns
    * VOID
    */
    void add(const f32& f);
    /**@brief Adds a f64 to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] f
    * @returns
    * VOID
    */
    void add(const f64& f);
    /**@brief Adds a c style string and the string length to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] string
    * @returns
    * VOID
    */
    void add(const char* string);
    /**@brief Adds a std::string and the string length to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] string
    * @returns
    * VOID
    */
    void add(const std::string& string);
    /**@brief Adds a String and the string length to the buffer. If the buffer to small to add the new data it will automatically allocate mor memory
    * @param[in] string
    * @returns
    * VOID
    */
    void add(const String& string);

    /**@brief Gets a i8 from the buffer
    * @returns
    * Returns a int8_t from the buffer
    */
    i8 getI8();
    /**@brief Gets a i16 from the buffer
     * @returns
     * Returns a int16_t from the buffer
     */
    i16 getI16();
    /**@brief Gets a i132 from the buffer
     * @returns
     * Returns a int32_t from the buffer
     */
    i32 getI32();
    /**@brief Gets a i64 from the buffer
     * @returns
     * Returns a int64_t from the buffer
     */
    i64 getI64();
    /**@brief Gets a ui8 from the buffer
     * @returns
     * Returns a uint8_t from the buffer
     */
    ui8 getUi8();
    /**@brief Gets a ui16 from the buffer
     * @returns
     * Returns a uint16_t from the buffer
     */
    ui16 getUi16();
    /**@brief Gets a ui32 from the buffer
     * @returns
     * Returns a uint32_t from the buffer
     */
    ui32 getUi32();
    /**@brief Gets a ui64 from the buffer
     * @returns
     * Returns a uint64_t from the buffer
     */
    ui64 getUi64();
    /**@brief Gets a f32 from the buffer
     * @returns
     * Returns a float from the buffer
     */
    f32 getF32();
    /**@brief Gets a f64 from the buffer
     * @returns
     * Returns a double from the buffer
     */
    f64 getF64();
    /**@brief Gets a c style string from the buffer
     * @returns
     * Returns a c style string from the buffer. This should not be freed or modified. For modification it should be allocated a new c style string.
     */
    char* getC_str();
    /**@brief Gets a std::string from the buffer
     * @returns
     * Returns a std::string from the buffer
     */
    std::string getSTD_str();
    /**@brief Gets a String from the buffer
     * @returns
     * Returns a String from the buffer
     */
    String getString();

    /**@brief Gets the length of the buffer
     * @returns
     * Returns the length of the data is stored in the buffer
     */
    const ui64& length() const;
    /**@brief Gets the capacity of the buffer
     * @returns
     * Returns the capacity of the buffer
     */
    const ui64& capacity() const;
    /**@brief Gets the buffer data
     * @returns
     * Returns a ui8* to the buffer data
     */
    ui8* getSource() const;

    /**@brief Checks if the buffer is filled with data
     * @retval TRUE     if the buffer has data
     * @retval FALSE    if the buffer has no data
     */
    bool hasData() const;
    /**@brief Clears the buffer and sets all values to 0
     * @returns
     * VOID
     */
    void clear();
private:
    bool checkCap(const ui64& size) const;
    void reserve(const ui64& size);
    void makeFit(const ui64& size);

private:
    ui8* mSource;
    ui64 mCap;
    ui64 mLen;
    ui64 mRead;
};

#endif //PLAYGROUNDLIB_BINARYBUFFER_H
