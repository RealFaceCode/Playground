#include "../../../hdr/util/buffer/binarybuffer.h"
#include "../../../hdr/util/memory.h"
#include "../../../hdr/util/buffer/string.h"

BinaryBuffer::BinaryBuffer()
    :mSource(nullptr), mLen(0), mCap(0), mRead(0)
{}

BinaryBuffer::BinaryBuffer(const ui64 &bufferLen)
    :mSource(nullptr), mLen(0), mCap(0), mRead(0)
{
    reserve(bufferLen);
}

BinaryBuffer::~BinaryBuffer()
{
    clear();
}

void BinaryBuffer::push(const ui64 &size, void *data)
{
    if(!checkCap(size))
    {
        makeFit(size);
    }

    memcpy(mSource + mLen, data, size);
    mLen += size;
}

void *BinaryBuffer::pop(const ui64 &size)
{
    if((mRead + size) > mCap)
    {
        return nullptr;
    }

    ui64 offset = mRead;
    mRead += size;
    return (void*)(mSource + offset);
}

void BinaryBuffer::add(const i8& integer)
{
    push(sizeof(i8), (void*)&integer);
}

void BinaryBuffer::add(const i16& integer)
{
    push(sizeof(i16), (void*)&integer);
}

void BinaryBuffer::add(const i32& integer)
{
    push(sizeof(i32), (void*)&integer);
}

void BinaryBuffer::add(const i64& integer)
{
    push(sizeof(i64), (void*)&integer);
}

void BinaryBuffer::add(const ui8& integer)
{
    push(sizeof(ui8), (void*)&integer);
}

void BinaryBuffer::add(const ui16& integer)
{
    push(sizeof(ui16), (void*)&integer);
}

void BinaryBuffer::add(const ui32& integer)
{
    push(sizeof(ui32), (void*)&integer);
}

void BinaryBuffer::add(const ui64& integer)
{
    push(sizeof(ui64), (void*)&integer);
}

void BinaryBuffer::add(const f32& f)
{
    push(sizeof(f32), (void*)&f);
}

void BinaryBuffer::add(const f64& f)
{
    push(sizeof(f64), (void*)&f);
}

void BinaryBuffer::add(const char* string, const bool& withoutLen)
{
    ui64 strLen = strlen(string) + 1;
    if(!withoutLen)
    {
        add(strLen);
    }
    push(strLen, (void*)string);
}

void BinaryBuffer::add(const std::string& string, const bool& withoutLen)
{
    ui64 strLen = string.length() + 1;
    if(!withoutLen)
    {
        add(strLen);
    }
    push(strLen, (void*)string.data());
}

void BinaryBuffer::add(const String& string, const bool& withoutLen)
{
    ui64 strLen = string.length() + 1;
    if(!withoutLen)
    {
        add(strLen);
    }
    push(strLen, (void*)string.getSource());
}

i8 BinaryBuffer::getI8()
{
    return *(i8*)pop(sizeof(i8));
}

i16 BinaryBuffer::getI16()
{
    return *(i16*)pop(sizeof(i16));
}

i32 BinaryBuffer::getI32()
{
    return *(i32*)pop(sizeof(i32));
}

i64 BinaryBuffer::getI64()
{
    return *(i64*)pop(sizeof(i64));
}

ui8 BinaryBuffer::getUi8()
{
    return *(ui8*)pop(sizeof(ui8));
}

ui16 BinaryBuffer::getUi16()
{
    return *(ui16*)pop(sizeof(ui16));
}

ui32 BinaryBuffer::getUi32()
{
    return *(ui32*)pop(sizeof(ui32));
}

ui64 BinaryBuffer::getUi64()
{
    return *(ui64*)pop(sizeof(ui64));
}

f32 BinaryBuffer::getF32()
{
    return *(f32*)pop(sizeof(f32));
}

f64 BinaryBuffer::getF64()
{
    return *(f64*)pop(sizeof(f64));
}

char* BinaryBuffer::getC_str(const bool& withoutLen)
{
    if(!withoutLen)
    {
        ui64 strLen = getUi64();
        return (char*)pop(strLen);
    }

    int length = 0;
    for(ui64 i = mRead; i < mLen; i++)
    {
        if(mSource[i] == '\0')
        {
            length++;
            break;
        }
        length++;
    }

    return (char*)pop(length);
}

std::string BinaryBuffer::getSTD_str(const bool& withoutLen)
{
    if(!withoutLen)
    {
        ui64 strLen = getUi64();
        return {(char*)pop(strLen)};
    }

    int length = 0;
    for(ui64 i = mRead; i < mLen; i++)
    {
        if(mSource[i] == '\0')
        {
            length++;
            break;
        }
        length++;
    }

    std::string string;
    char* buffer = (char*)pop(length);
    string = buffer;
    return string;
}

String BinaryBuffer::getString(const bool& withoutLen)
{
    if(!withoutLen)
    {
        ui64 strLen = getUi64();
        return {(char*)pop(strLen)};
    }

    int length = 0;
    for(ui64 i = mRead; i < mLen; i++)
    {
        if(mSource[i] == '\0')
        {
            length++;
            break;
        }
        length++;
    }

    String string;
    char* buffer = (char*)pop(length);
    string.add(buffer);
    return string;
}

const ui64 &BinaryBuffer::length() const {
    return mLen;
}

const ui64& BinaryBuffer::capacity() const {
    return mCap;
}

const ui64 &BinaryBuffer::readOffset() const
{
    return mRead;
}

ui8 *BinaryBuffer::getSource() const {
    return mSource;
}

bool BinaryBuffer::hasData() const {
    return (mRead <= mLen);
}

void BinaryBuffer::clear()
{
    if(mSource != nullptr)
    {
        Free(mSource);
        mSource = nullptr;
    }

    mLen = 0;
    mCap = 0;
    mRead = 0;
}

bool BinaryBuffer::checkCap(const ui64 &size) const
{
    return (mLen + size) <= mCap;
}

void BinaryBuffer::reserve(const ui64 &size)
{
    if(mSource == nullptr)
    {
        mSource = (ui8*)Malloc(size + 1);
        mCap = size;
    }
    else
    {
        mSource = (ui8*)Realloc(mSource, mCap + size + 1);
        mCap += size;
    }
}

void BinaryBuffer::makeFit(const ui64 &size)
{
    ui64 len = size;
    len -= (mCap - mLen);
    reserve(len);
}