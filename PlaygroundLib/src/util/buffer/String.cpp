#include "../../../hdr/util/buffer/string.h"
#include "../../../hdr/util/memory.h"
#include "../../../hdr/logger.h"

String toString(i8 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(i16 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(i32 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(i64 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(ui8 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(ui16 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(ui32 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(ui64 integer)
{
    char str[32];
    snprintf(str, 32, "%d", integer);
    return str;
}

String toString(f32 f)
{
    char str[32];
    snprintf(str, 32, "%f", f);
    return str;
}

String toString(f64 f)
{
    char str[64];
    snprintf(str, 64, "%f", f);
    return str;
}

String toString(bool boolean, bool asNum)
{
    if(asNum)
    {
        char str[32];
        snprintf(str, 32, "%d", boolean);
        return str;
    }

    if(boolean)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

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
    insert(mLen, string);
}

void String::add(const std::string& string)
{
    insert(mLen, string);
}

void String::add(const char* string)
{
    insert(mLen, string);
}

void String::add(i8 integer)
{
    add(toString(integer));
}

void String::add(i16 integer)
{
    add(toString(integer));
}

void String::add(i32 integer)
{
    add(toString(integer));
}

void String::add(i64 integer)
{
    add(toString(integer));
}

void String::add(ui8 integer)
{
    add(toString(integer));
}

void String::add(ui16 integer)
{
    add(toString(integer));
}

void String::add(ui32 integer)
{
    add(toString(integer));
}

void String::add(ui64 integer)
{
    add(toString(integer));
}

void String::add(f32 f)
{
    add(toString(f));
}

void String::add(f64 f)
{
    add(toString(f));
}

void String::add(bool boolean, bool asNum)
{
    if(asNum)
    {
        char str[32];
        snprintf(str, 32, "%d", boolean);
        add(str);
        return;
    }

    if(boolean)
    {
        add("true");
    }
    else
    {
        add("false");
    }

}

void String::replaceWith(const String& string, const String& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.mLen) - (pos.size() * string.mLen);
    if(!checkCap(cap))
    {
        makeFit(cap);
    }

    for(ui64 p : pos)
    {
        remove(p, p + string.mLen);
        insert(p - string.mLen, rString);
    }
}

void String::replaceWith(const ui64& posBegin, const ui64& posEnd, const String& string)
{
    remove(posBegin, posEnd);
    insert(posBegin, string);
}

void String::replaceWith(const String& string, const std::string& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.size()) - (pos.size() * string.mLen);
    if(!checkCap(cap))
    {
        makeFit(cap);
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
    remove(posBegin, posEnd);
    insert(posBegin, string);
}

void String::replaceWith(const String& string, const char* rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * strlen(rString)) - (pos.size() * string.mLen);
    if(!checkCap(cap))
    {
        makeFit(cap);
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
    remove(posBegin, posEnd);
    insert(posBegin, string);
}

void String::replaceWith(const std::string& string, const String& rString)
{
    std::vector<ui64> pos = find(string);
    ui64 cap = (pos.size() * rString.mLen) - (pos.size() * string.size());
    if(!checkCap(cap))
    {
        makeFit(cap);
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
        makeFit(cap);
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
        makeFit(cap);
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
        makeFit(cap);
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
        makeFit(cap);
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
        makeFit(cap);
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
        makeFit(strLen);
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
        makeFit(strLen);
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
        makeFit(strLen);
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
    ui64 strLen = string.length();
    for(ui64 i = 0; i < mLen; i++)
    {
        if(mSource[i] == string.getSource()[0])
        {
            StringView view(i, i + strLen - 1, *this);
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
            StringView view(i, i + strLen - 1, *this);
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
            StringView view(i, i + strLen - 1, *this);
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
    ui64 strLen = string.length();
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        if(mSource[i] == string.at(i))
        {
            StringView view = createStringView(i, i + strLen -1);
            if(strcmp((const char*)view.getView(), string.c_str()) == 0)
            {
                pos.emplace_back(i);
                i += strLen;
            }
        }
    }
    return pos;
}

const std::vector<ui64> String::find(const ui64& posBegin, const ui64& posEnd, const std::string& string) const
{
    std::vector<ui64> pos = {};
    ui64 strLen = string.length();
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        if(mSource[i] == string[i])
        {
            StringView view = createStringView(i, i + strLen -1);
            if(strcmp((const char*)view.getView(), string.c_str()) == 0)
            {
                pos.emplace_back(i);
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
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        if(mSource[i] == string[i])
        {
            StringView view = createStringView(i, i + strLen -1);
            if(strcmp((const char*)view.getView(), string) == 0)
            {
                pos.emplace_back(i);
                i += strLen;
            }
        }
    }
    return pos;
}

ui64 String::findFirst(const String &string) const
{
    for(ui64 i = 0; i < mLen; i++)
    {
        if(mSource[i] == string.c_str()[0])
        {
            StringView view(i, i + string.length() - 1, *this);
            if(strcmp(string.c_str(), (const char*)view.getView()) == 0)
            {
                return i;
            }
        }
    }
    return UINT64_MAX;
}

ui64 String::findFirst(const std::string &string) const
{
    for(ui64 i = 0; i < mLen; i++)
    {
        if(mSource[i] == string.c_str()[0])
        {
            StringView view(i, i + string.length() - 1, *this);
            if(strcmp(string.c_str(), (const char*)view.getView()) == 0)
            {
                return i;
            }
        }
    }
    return UINT64_MAX;
}

ui64 String::findFirst(const char *string) const
{
    for(ui64 i = 0; i < mLen; i++)
    {
        if(mSource[i] == string[0])
        {
            StringView view(i, i + strlen(string) - 1 , *this);
            if(strcmp(string, (const char*)view.getView()) == 0)
            {
                return i;
            }
        }
    }
    return UINT64_MAX;
}

ui64 String::findFirst(const ui64 &posBegin, const ui64 &posEnd, const String &string) const
{
    ui64 strLen = string.length();
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        if(mSource[i] == string.at(0))
        {
            StringView view = createStringView(i, i + strLen -1);
            if(strcmp((const char*)view.getView(), string.c_str()) == 0)
            {
                return i;
            }
        }
    }
    return UINT64_MAX;
}

ui64 String::findFirst(const ui64 &posBegin, const ui64 &posEnd, const std::string &string) const
{
    ui64 strLen = string.length();
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        if(mSource[i] == string[0])
        {
            StringView view = createStringView(i, i + strLen -1);
            if(strcmp((const char*)view.getView(), string.c_str()) == 0)
            {
                return i;
            }
        }
    }
    return UINT64_MAX;
}

ui64 String::findFirst(const ui64 &posBegin, const ui64 &posEnd, const char *string) const
{
    ui64 strLen = strlen(string);
    for(ui64 i = posBegin; i < posEnd; i++)
    {
        if(mSource[i] == string[0])
        {
            StringView view = createStringView(i, i + strLen -1);
            if(strcmp((const char*)view.getView(), string) == 0)
            {
                return i;
            }
        }
    }
    return UINT64_MAX;
}

std::vector<String> String::toLines() const
{
    std::vector<String> lines;

    std::vector<ui64> pos = find("\n");
    ui64 begin = 0;
    for(ui64 p : pos)
    {
        StringView view = createStringView(begin, p);
        lines.emplace_back((const char*)view.getView());
        begin = ++p;
    }

    return lines;
}

std::vector<String> String::tokenize(const char &token) const
{
    std::vector<String> tokens;
    const char* t = &token;
    ui64 pos = findFirst(t);
    if(pos == UINT64_MAX)
    {
        StringView view = createStringView(0, mLen);
        tokens.emplace_back((const char*)view.getView());
    }

    ui64 nPos = findFirst(pos + 1, mLen, t);
    if(pos < mLen)
    {
        StringView view = createStringView(0, pos - 1);
        tokens.emplace_back((const char*)view.getView());
    }

    while(pos < mLen)
    {
        if(nPos == UINT64_MAX)
        {
            StringView view = createStringView(pos + 1, mLen - 1);
            tokens.emplace_back((const char*)view.getView());
            break;
        }

        StringView view = createStringView(pos + 1, nPos - 1);
        tokens.emplace_back((const char*)view.getView());
        pos = findFirst(pos + 1, mLen, t);
        nPos = findFirst(pos + 1, mLen, t);
    }

    return tokens;
}

StringView String::createStringView(const ui64& posBegin, const ui64& posEnd) const
{
    return {posBegin, posEnd, *this};
}

bool String::reserve(const ui64& size)
{
    //TODO: error handling
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
    if(mSource)
    {
        mSource[mLen] = '\0';
    }
}

void String::initialize()
{
    mSource = nullptr;
    mLen = 0;
    mCap = 0;
}

const ui64& String::capacity() const
{
    return mCap;
}

const ui64& String::length() const
{
    return mLen;
}

bool String::empty() const
{
    return mLen <= 0;
}

ui8* String::getSource() const
{
    return mSource;
}

const char *String::c_str() const {
    return (const char*)mSource;
}

const ui8& String::at(const ui64& index) const
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

bool String::checkCap(const ui64& size) const
{
    return mCap - mLen >= size;
}

void String::makeFit(const ui64 &size) {
    ui64 strLen = size;
    strLen -= (mCap - mLen);
    reserve(strLen);
}

bool String::operator<(const String &other) const
{
    return mLen < other.mLen;
}

bool String::operator>(const String &other) const
{
    return mLen > other.mLen;
}

bool String::operator==(const String &other)
{
    return mLen == other.mLen && (strcmp((const char*)mSource, (const char*)other.mSource) == 0);
}

bool String::operator<=(const String &other) const
{
    return mLen <= other.mLen;
}

bool String::operator>=(const String &other) const
{
    return mLen >= other.mLen;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const String& string)
{
    ui64 strLen = posEnd - posBegin + 1;
    mSource = (ui8*)Malloc(strLen + 1);
    memcpy(mSource, string.getSource() + posBegin, strLen);
    mSource[strLen] = '\0';
    mLen = strLen;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const std::string& string)
{
    ui64 strLen = posEnd - posBegin + 1;
    mSource = (ui8*)Malloc(strLen + 1);
    memcpy(mSource, string.data() + posBegin, strLen);
    mSource[strLen] = '\0';
    mLen = strLen;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const char* string)
{
    ui64 strLen = posEnd - posBegin + 1;
    mSource = (ui8*)Malloc(strLen + 1);
    memcpy(mSource, string + posBegin, strLen);
    mSource[strLen] = '\0';
    mLen = strLen;
}

StringView::StringView(const ui64& posBegin, const ui64& posEnd, const StringView& string)
{
    ui64 strLen = posEnd - posBegin + 1;
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

const ui64& StringView::length() const
{
    return mLen;
}

const ui8* StringView::getView() const
{
    return mSource;
}