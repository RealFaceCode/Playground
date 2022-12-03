//
// Created by Kevin-Laptop on 13.11.2022.
//

#include "../../hdr/util/string.h"
#include "../../hdr/util/memory.h"
#include "../../hdr/logger.h"

String::String() :mCap(0), mLen(0), mSource(nullptr) {}

String::String(const String& string)
    :mCap(string.mCap), mLen(string.mLen), mSource(nullptr)
{
    reserve(mCap);
    memcpy(mSource, string.mSource, mCap);
}

String::String(const std::string& string)
    :mCap(string.capacity()), mLen(string.length()), mSource(nullptr)
{
    reserve(mCap);
    memcpy(mSource, string.data(), mCap);
}

String::String(const char* string)
    :mCap(strlen(string)), mLen(mCap), mSource(nullptr)
{
    reserve(mCap);
    memcpy(mSource, string, mCap);
}

String::~String()
{
    if(mSource != nullptr)
    {
        Free(mSource);
    }
    mSource = nullptr;
    mCap = 0;
    mLen = 0;
}

void String::add(const String& string)
{
    ui64 strLen = string.mLen;

    if(!checkCap(strLen))
    {
        strLen -= mCap;
        reserve(strLen);
    }
    insert(mLen, string);
}

void String::add(const std::string& string)
{
    ui64 strLen = string.size();
    if(!checkCap(strLen))
    {
        strLen -= mCap;
        reserve(strLen);
    }
    insert(mLen, string);
}

void String::add(const char* string)
{
    ui64 strLen = strlen(string);
    if(!checkCap(strLen))
    {
        strLen -= mCap;
        reserve(strLen);
    }
    insert(mLen, string);
}


void String::replaceWith(const String& string, const String& rString)
{
    std::vector<ui64> pos = find(string);
    if(!checkCap((pos.size() * rString.mLen) - (pos.size() * string.mLen)))
    {
        reserve((pos.size() * rString.mLen) - (pos.size() * string.mLen));
    }

    for(ui64 p : pos)
    {
        remove(p, p + string.mLen);
        insert(p - string.mLen, rString);
    }
}

void String::replaceWith(const ui64& posBegin, const ui64& posEnd, const String& string)
{
}

void String::replaceWith(const String& string, const std::string& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.size()) - (pos.size() * string.mLen);
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + string.mLen);
        insert(p, rString);
        offSet += rString.size() - string.mLen;
    }
}

void String::replaceWith(const ui64& posBegin, const ui64& posEnd, const std::string& string)
{
}

void String::replaceWith(const String& string, const char* rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * strlen(rString)) - (pos.size() * string.mLen);
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + string.mLen);
        insert(p, rString);
        offSet += strlen(rString) - string.mLen;
    }
}

void String::replaceWith(const ui64& posBegin, const ui64& posEnd, const char* string)
{
}

void String::replaceWith(const std::string& string, const String& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.mLen) - (pos.size() * string.size());
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + string.size());
        insert(p, rString);
        offSet += rString.mLen - string.size();
    }
}

void String::replaceWith(const std::string& string, const std::string& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.size()) - (pos.size() * string.size());
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + string.size());
        insert(p, rString);
        offSet += rString.size() - string.size();
    }
}

void String::replaceWith(const std::string& string, const char* rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * strlen(rString)) - (pos.size() * string.size());
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + string.size());
        insert(p, rString);
        offSet += strlen(rString) - string.size();
    }
}

void String::replaceWith(const char* string, const String& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.mLen) - (pos.size() * strlen(string));
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + strlen(string));
        insert(p, rString);
        offSet += rString.mLen - strlen(string);
    }
}

void String::replaceWith(const char* string, const std::string& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.size()) - (pos.size() * strlen(string));
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + strlen(string));
        insert(p, rString);
        offSet += rString.size() - strlen(string);
    }
}

void String::replaceWith(const char* string, const char* rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * strlen(rString)) - (pos.size() * strlen(string));
    if(!checkCap(cap))
    {
        cap -= (mCap - mLen);
        reserve(cap);
    }

    ui64 offSet = 0;
    for(ui64 p : pos)
    {
        p += offSet;
        remove(p, p + strlen(string));
        insert(p, rString);
        offSet += strlen(rString) - strlen(string);
    }
}

void String::insert(const ui64& pos, const String& string)
{
    ui64 strLen = string.mLen;
    if(!checkCap(strLen))
    {
        reserve(strLen);
    }

    ui64 bufLen = mLen - pos;
    ui8* buffer = (ui8*)Malloc(bufLen);
    memcpy(buffer, mSource + pos, bufLen);
    memcpy(mSource + pos, string.mSource, strLen);
    memcpy(mSource + pos + strLen, buffer, bufLen);
    Free(buffer);
    mLen += strLen;
}

void String::insert(const ui64& pos, const std::string& string)
{
    ui64 strLen = string.size();
    if(!checkCap(strLen))
    {
        reserve(strLen);
    }

    ui64 bufLen = mLen - pos;
    ui8* buffer = (ui8*)Malloc(bufLen);
    memcpy(buffer, mSource + pos, bufLen);
    memcpy(mSource + pos, string.data(), strLen);
    memcpy(mSource + pos + strLen, buffer, bufLen);
    Free(buffer);
    mLen += strLen;
}

void String::insert(const ui64& pos, const char* string)
{
    ui64 strLen = strlen(string);
    if(!checkCap(strLen))
    {
        reserve(strLen);
    }

    ui64 bufLen = mLen - pos;
    ui8* buffer =  nullptr;
    if(bufLen > 0)
    {
        buffer = (ui8*)Malloc(bufLen);
        memcpy(buffer, mSource + pos, bufLen);
    }

    memcpy(mSource + pos, string, strLen);

    if(buffer != nullptr)
    {
        memcpy(mSource + pos + strLen, buffer, bufLen);
    }

    Free(buffer);
    mLen += strLen;
    if(mSource[mLen] != '\0')
    {
        mSource[mLen] = '\0';
    }
}

void String::remove(const ui64& posBegin, const ui64& posEnd)
{
    if(posBegin >= 0 && posBegin < mLen && posEnd >= 0 && posEnd <= mLen)
    {
        ui64 strLen = posEnd - posBegin;
        ui64 bufLen = mLen - posEnd;
        if(bufLen == 0)
        {
            bufLen += strLen;
        }
        memmove(mSource + posBegin, mSource + posEnd, bufLen + 1);
        mLen -= strLen;
    }
}

void String::remove(const ui64& posBegin, const ui64& posEnd, const String& string)
{
    if(posBegin >= 0 && posBegin < mLen && posEnd >= 0 && posEnd < mLen)
    {
        std::vector<ui64> pos = find(posBegin, posEnd, string);
        ui64 strLen = string.mLen;
        ui64 off = 0;
        for(int i = 0; i < pos.size(); i++)
        {
            pos.at(i) -= off;
            remove(pos.at(i), pos.at(i) + strLen);
            off += strLen;
        }
    }
}

void String::remove(const ui64& posBegin, const ui64& posEnd, const std::string& string)
{
    if(posBegin >= 0 && posBegin < mLen && posEnd >= 0 && posEnd < mLen)
    {
        std::vector<ui64> pos = find(posBegin, posEnd, string);
        ui64 strLen = string.size();
        ui64 off = 0;
        for(int i = 0; i < pos.size(); i++)
        {
            pos.at(i) -= off;
            remove(pos.at(i), pos.at(i) + strLen);
            off += strLen;
        }
    }
}

void String::remove(const ui64& posBegin, const ui64& posEnd, const char* string)
{
    if(posBegin >= 0 && posBegin < mLen && posEnd >= 0 && posEnd < mLen)
    {
        std::vector<ui64> pos = find(posBegin, posEnd, string);
        ui64 strLen = strlen(string);
        ui64 off = 0;
        for(int i = 0; i < pos.size(); i++)
        {
            pos.at(i) -= off;
            remove(pos.at(i), pos.at(i) + strLen);
            off += strLen;
        }
    }
}

void String::remove(const String& string)
{
    std::vector<ui64> pos = find(string);
    ui64 offset = 0;
    for(ui64 p : pos)
    {
        p -= offset;
        remove(p, p + string.mLen);
        offset += string.mLen;
    }
}

void String::remove(const std::string& string)
{
    std::vector<ui64> pos = find(string);
    ui64 offset = 0;
    for(ui64 p : pos)
    {
        p -= offset;
        remove(p, p + string.size());
        offset += string.size();
    }
}

void String::remove(const char* string)
{
    std::vector<ui64> pos = find(string);
    ui64 offset = 0;
    for(ui64 p : pos)
    {
        p -= offset;
        remove(p, p + strlen(string));
        offset += strlen(string);
    }
}

void String::toUpper()
{
    for(ui64 i =  0; i < mLen; i++)
    {
        mSource[i] = (ui8) std::toupper(mSource[i]);
    }
}

void String::toUpper(const ui64& posBegin, const ui64& posEnd)
{
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        mSource[i] = (ui8) std::toupper(mSource[i]);
    }
}

void String::toUpper(const ui64& posBegin, const ui64& posEnd, const String& string)
{
    std::vector<ui64> pos = find(posBegin, posEnd, string);
    for(ui64 p : pos)
    {
        ui64 strLen = string.mLen;
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::toupper(mSource[i]);
        }
    }
}

void String::toUpper(const ui64& posBegin, const ui64& posEnd, const std::string& string)
{
    std::vector<ui64> pos = find(posBegin, posEnd, string);
    for(ui64 p : pos)
    {
        ui64 strLen = string.size();
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::toupper(mSource[i]);
        }
    }
}

void String::toUpper(const ui64& posBegin, const ui64& posEnd, const char* string)
{
    std::vector<ui64> pos = find(posBegin, posEnd, string);
    for(ui64 p : pos)
    {
        ui64 strLen = strlen(string);
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::toupper(mSource[i]);
        }
    }
}

void String::toUpper(const String& string)
{
    std::vector<ui64> pos = find(string);
    ui64 strLen = string.mLen;
    for(ui64 p : pos)
    {
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::toupper(mSource[i]);
        }
    }
}

void String::toUpper(const std::string& string)
{
    std::vector<ui64> pos = find(string);
    ui64 strLen = string.size();
    for(ui64 p : pos)
    {
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::toupper(mSource[i]);
        }
    }
}

void String::toUpper(const char* string)
{
    std::vector<ui64> pos = find(string);
    ui64 strLen = strlen(string);
    for(ui64 p : pos)
    {
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::toupper(mSource[i]);
        }
    }
}

void String::toLower()
{
    for(ui64 i =  0; i < mLen; i++)
    {
        mSource[i] = (ui8) std::tolower(mSource[i]);
    }

}

void String::toLower(const ui64& posBegin, const ui64& posEnd)
{
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        mSource[i] = (ui8) std::tolower(mSource[i]);
    }
}

void String::toLower(const ui64& posBegin, const ui64& posEnd, const String& string)
{
    std::vector<ui64> pos = find(posBegin, posEnd, string);
    for(ui64 p : pos)
    {
        ui64 strLen = string.mLen;
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::tolower(mSource[i]);
        }
    }
}

void String::toLower(const ui64& posBegin, const ui64& posEnd, const std::string& string)
{
    std::vector<ui64> pos = find(posBegin, posEnd, string);
    for(ui64 p : pos)
    {
        ui64 strLen = string.size();
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::tolower(mSource[i]);
        }
    }
}

void String::toLower(const ui64& posBegin, const ui64& posEnd, const char* string)
{
    std::vector<ui64> pos = find(posBegin, posEnd, string);
    for(ui64 p : pos)
    {
        ui64 strLen = strlen(string);
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::tolower(mSource[i]);
        }
    }
}

void String::toLower(const String& string)
{
    std::vector<ui64> pos = find(string);
    ui64 strLen = string.mLen;
    for(ui64 p : pos)
    {
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::tolower(mSource[i]);
        }
    }
}

void String::toLower(const std::string& string)
{
    std::vector<ui64> pos = find(string);
    ui64 strLen = string.size();
    for(ui64 p : pos)
    {
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::tolower(mSource[i]);
        }
    }
}

void String::toLower(const char* string)
{
    std::vector<ui64> pos = find(string);
    ui64 strLen = strlen(string);
    for(ui64 p : pos)
    {
        for(ui64 i = p; i < p + strLen; i++)
        {
            mSource[i] = (ui8) std::tolower(mSource[i]);
        }
    }
}

const std::vector<ui64> String::find(const String& string) const
{
    std::vector<ui64> pos = {};
    ui64 strLen = string.getLength();
    for(ui64 i = 0; i < mLen; i++)
    {
        if(mSource[i] == string.getSource()[0])
        {
            StringView view(i, i + strLen, *this);
            if(strcmp((const char*)string.getSource(), (const char*)view.getView()) == 0)
            {
                pos.emplace_back(i);
                i += strLen;
            }
        }
    }
    return pos;
}

const std::vector<ui64> String::find(const std::string& string) const
{
    std::vector<ui64> pos = {};
    ui64 strLen = string.size();
    for(ui64 i = 0; i < mLen; i++)
    {
        if(mSource[i] == string.data()[0])
        {
            StringView view(i, i + strLen, *this);
            if(strcmp((const char*)string.data(), (const char*)view.getView()) == 0)
            {
                pos.emplace_back(i);
                i += strLen;
            }
        }
    }
    return pos;
}
const std::vector<ui64> String::find(const char* string) const
{
    std::vector<ui64> pos = {};
    ui64 strLen = strlen(string);
    for(ui64 i = 0; i < mLen; i++)
    {
        if(mSource[i] == string[0])
        {
            StringView view(i, i + strLen, *this);
            if(strcmp(string, (const char*)view.getView()) == 0)
            {
                pos.emplace_back(i);
                i += strLen;
            }
        }
    }
    return pos;
}

const std::vector<ui64> String::find(const ui64& posBegin, const ui64& posEnd, const String& string) const
{
    std::vector<ui64> pos = {};
    ui64 strLen = string.getLength();
    StringView strView(posBegin, posEnd, *this);
    for(ui64 i = 0; i < mLen; i++)
    {
        if(strView.getView()[i] == string.getSource()[0])
        {
            StringView view(i, i + strLen, strView);
            if(strcmp((const char*)string.getSource(), (const char*)view.getView()) == 0)
            {
                pos.emplace_back(i + posBegin);
                i += strLen;
            }
        }
    }
    return pos;
}

const std::vector<ui64> String::find(const ui64& posBegin, const ui64& posEnd, const std::string& string) const
{
    std::vector<ui64> pos = {};
    ui64 strLen = string.size();
    StringView strView(posBegin, posEnd, *this);
    for(ui64 i = 0; i < mLen; i++)
    {
        if(strView.getView()[i] == string.data()[0])
        {
            StringView view(i, i + strLen, strView);
            if(strcmp((const char*)string.data(), (const char*)view.getView()) == 0)
            {
                pos.emplace_back(i + posBegin);
                i += strLen;
            }
        }
    }
    return pos;
}

const std::vector<ui64> String::find(const ui64& posBegin, const ui64& posEnd, const char* string) const
{
    std::vector<ui64> pos = {};
    ui64 strLen = strlen(string);
    StringView strView(posBegin, posEnd, *this);
    for(ui64 i = 0; i < mLen; i++)
    {
        if(strView.getView()[i] == string[0])
        {
            StringView view(i, i + strLen, strView);
            if(strcmp((const char*)string, (const char*)view.getView()) == 0)
            {
                pos.emplace_back(i + posBegin);
                i += strLen;
            }
        }
    }
    return pos;
}

const bool String::reserve(const ui64& size)
{
    //TODO: error handling
    if(mSource == nullptr)
    {
        mSource = (ui8*)Malloc(size + 1);
        mCap = size;
    }
    else
    {
        mSource = (ui8*)Realloca(mSource, mCap + size + 1);
        mCap += size;
    }

    if(mSource == nullptr)
    {
        return false;
    }

    mSource[mCap] = '\0';

    return true;
}

void String::clear()
{
    mLen = 0;
    mSource[mLen] = '\0';
}

const ui64 String::getCapacity() const
{
    return mCap;
}

const ui64 String::getLength() const
{
    return mLen;
}

ui8* String::getSource() const
{
    return mSource;
}

const ui8& String::at(const ui64 index) const
{
   if(index >= mLen || index < 0 || mLen == 0)
   {
       LOG_ASSERT(true, {}, "String is Empty or index is higher than mLen, lower than 0 or index is lower than 0.\nIndex: %i, mLen: %i", index, mLen);
   }

    return mSource[index];
}

String& String::operator=(const String& string)
{
    clear();
    add(string);
    return *this;
}

String& String::operator=(const std::string& string)
{
    clear();
    add(string);
    return *this;
}

String& String::operator=(const char* string)
{
    clear();
    add(string);
    return *this;
}

String String::operator+(const String& string)
{
    String rString(*this);
    rString.add(string);
    return rString;
}

String String::operator+(const std::string& string)
{
    String rString(*this);
    rString.add(string);
    return rString;
}

String String::operator+(const char* string)
{
    String rString(*this);
    rString.add(string);
    return rString;
}

String& String::operator+=(const String& string)
{
    add(string);
    return *this;
}

String& String::operator+=(const std::string& string)
{
    add(string);
    return *this;
}

String& String::operator+=(const char* string)
{
    add(string);
    return *this;
}

bool String::checkCap(const ui64& size)
{
    return mCap - mLen >= size ? true : false;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const String& string)
{
    ui64 strLen = posEnd - posBegin;
    mSource = (ui8*)Malloc(strLen + 1);
    memcpy(mSource, string.getSource() + posBegin, strLen);
    mSource[strLen] = '\0';
    mLen = strLen;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const std::string string)
{
    ui64 strLen = posEnd - posBegin;
    mSource = (ui8*)Malloc(strLen + 1);
    memcpy(mSource, string.data() + posBegin, strLen);
    mSource[strLen] = '\0';
    mLen = strLen;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const char* string)
{
    ui64 strLen = posEnd - posBegin;
    mSource = (ui8*)Malloc(strLen + 1);
    memcpy(mSource, string + posBegin, strLen);
    mSource[strLen] = '\0';
    mLen = strLen;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const StringView& string)
{
    ui64 strLen = posEnd - posBegin;
    mSource = (ui8*)Malloc(strLen + 1);
    memcpy(mSource, string.getView() + posBegin, strLen);
    mSource[strLen] = '\0';
    mLen = strLen;
}

StringView::~StringView()
{
    if(mSource != nullptr)
    {
        Free(mSource);
    }
    mSource = nullptr;
    mLen = 0;
}

const ui64 StringView::getLen() const
{
    return mLen;
}

const ui8* StringView::getView() const
{
    return mSource;
}