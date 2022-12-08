#ifndef PLAYGROUNDLIB_BINARYBUFFER_H
#define PLAYGROUNDLIB_BINARYBUFFER_H
#include "../../core.h"
#include "string.h"

struct BinaryBuffer
{
public:
    BinaryBuffer();
    BinaryBuffer(const ui64& bufferLen);
    ~BinaryBuffer();

    void push(const ui64& size, void* data);
    void* pop(const ui64& size);

    void add(const i8& integer);
    void add(const i16& integer);
    void add(const i32& integer);
    void add(const i64& integer);
    void add(const ui8& integer);
    void add(const ui16& integer);
    void add(const ui32& integer);
    void add(const ui64& integer);
    void add(const f32& f);
    void add(const f64& f);
    void add(const char* string);
    void add(const std::string& string);
    void add(const String& string);

    i8 getI8();
    i16 getI16();
    i32 getI32();
    i64 getI64();
    ui8 getUi8();
    ui16 getUi16();
    ui32 getUi32();
    ui64 getUi64();
    f32 getF32();
    f64 getF64();
    char* getC_str();
    std::string getSTD_str();
    String getString();

    const ui64& length() const;
    const ui64& capacity() const;
    ui8* getSource() const;

    bool hasData() const;
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
