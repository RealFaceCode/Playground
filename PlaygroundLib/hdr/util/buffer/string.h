#include "../../core.h"

#ifndef PLAYGROUNDLIB_STRING_H
#define PLAYGROUNDLIB_STRING_H

struct String;

String toString(i8 integer);
String toString(i16 integer);
String toString(i32 integer);
String toString(i64 integer);
String toString(ui8 integer);
String toString(ui16 integer);
String toString(ui32 integer);
String toString(ui64 integer);
String toString(f32 f);
String toString(f64 f);
String toString(bool , bool asNum = false);

struct String
{
public:
    String();
    String(const String& string);
    String(const std::string& string);
    String(const char* string);

    ~String();

    void add(const String& string);
    void add(const std::string& string);
    void add(const char* string);
    void add(i8 integer);
    void add(i16 integer);
    void add(i32 integer);
    void add(i64 integer);
    void add(ui8 integer);
    void add(ui16 integer);
    void add(ui32 integer);
    void add(ui64 integer);
    void add(f32 f);
    void add(f64 f);
    void add(bool , bool asNum = false);

    void replaceWith(const String& string, const String& rString);
    void replaceWith(const ui64& posBegin, const ui64& posEnd, const String& string);
    void replaceWith(const String& string, const std::string& rString);
    void replaceWith(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    void replaceWith(const String& string, const char* rString);
    void replaceWith(const ui64& posBegin, const ui64& posEnd, const char* string);
    void replaceWith(const std::string& string, const String& rString);
    void replaceWith(const std::string& string, const std::string& rString);
    void replaceWith(const std::string& string, const char* rString);
    void replaceWith(const char* string, const String& rString);
    void replaceWith(const char* string, const std::string& rString);
    void replaceWith(const char* string, const char* rString);

    void insert(const ui64& pos, const String& string);
    void insert(const ui64& pos, const std::string& string);
    void insert(const ui64& pos, const char* string);

    void remove(const ui64& posBegin, const ui64& posEnd);
    void remove(const ui64& posBegin, const ui64& posEnd, const String& string);
    void remove(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    void remove(const ui64& posBegin, const ui64& posEnd, const char* string);
    void remove(const String& string);
    void remove(const std::string& string);
    void remove(const char* string);

   void toUpper();
   void toUpper(const ui64& posBegin, const ui64& posEnd);
   void toUpper(const ui64& posBegin, const ui64& posEnd, const String& string);
   void toUpper(const ui64& posBegin, const ui64& posEnd, const std::string& string);
   void toUpper(const ui64& posBegin, const ui64& posEnd, const char* string);
   void toUpper(const String& string);
   void toUpper(const std::string& string);
   void toUpper(const char* string);

    void toLower();
    void toLower(const ui64& posBegin, const ui64& posEnd);
    void toLower(const ui64& posBegin, const ui64& posEnd, const String& string);
    void toLower(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    void toLower(const ui64& posBegin, const ui64& posEnd, const char* string);
    void toLower(const String& string);
    void toLower(const std::string& string);
    void toLower(const char* string);

    const std::vector<ui64> find(const String& string) const;
    const std::vector<ui64> find(const std::string& string) const;
    const std::vector<ui64> find(const char* string) const;
    const std::vector<ui64> find(const ui64& posBegin, const ui64& posEnd, const String& string) const;
    const std::vector<ui64> find(const ui64& posBegin, const ui64& posEnd, const std::string& string) const;
    const std::vector<ui64> find(const ui64& posBegin, const ui64& posEnd, const char* string) const;

    const bool reserve(const ui64& size);
    void clear();

    const ui64 capacity() const;
    const ui64 length() const;
    ui8* getSource() const;
    const ui8& at(const ui64 index) const;

    String& operator=(const String& string);
    String& operator=(const std::string& string);
    String& operator=(const char* string);

    String operator+(const String& string);
    String operator+(const std::string& string);
    String operator+(const char* string);

    String& operator+=(const String& string);
    String& operator+=(const std::string& string);
    String& operator+=(const char* string);
private:
    bool checkCap(const ui64& size);
    void makeFit(const ui64& size);
private:
    ui64 mCap;
    ui64 mLen;
    ui8* mSource;
};

struct StringView
{
public:
    StringView(const ui64& posBegin, const ui64& posEnd, const String& string);
    StringView(const ui64& posBegin, const ui64& posEnd, const std::string string);
    StringView(const ui64& posBegin, const ui64& posEnd, const char* string);
    StringView(const ui64& posBegin, const ui64& posEnd, const StringView& string);
    ~StringView();

    const ui64& length() const;
    const ui8* getView() const;
private:
    ui64 mLen;
    ui8* mSource;
};
#endif //PLAYGROUNDLIB_STRING_H