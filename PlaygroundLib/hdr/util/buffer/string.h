#include "../../core.h"

#ifndef PLAYGROUNDLIB_STRING_H
#define PLAYGROUNDLIB_STRING_H

struct String;
/**@brief Converts a i8 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(i8 integer);
/**@brief Converts a i16 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(i16 integer);
/**@brief Converts a i32 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(i32 integer);
/**@brief Converts a i64 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(i64 integer);
/**@brief Converts a ui8 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(ui8 integer);
/**@brief Converts a ui16 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(ui16 integer);
/**@brief Converts a ui32 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(ui32 integer);
/**@brief Converts a ui64 to a string
 * @param[in] integer
 * @returns
 * Returns String with the given number as a string
 */
String toString(ui64 integer);
/**@brief Converts a f32 to a string
 * @param[in] f
 * @returns
 * Returns String with the given number as a string
 */
String toString(f32 f);
/**@brief Converts a f64 to a string
 * @param[in] f
 * @returns
 * Returns String with the given number as a string
 */
String toString(f64 f);
/**@brief Converts a bool to a string
 * @param[in] boolean
 * @param[in] asNum
 * @returns
 * Returns String with the given boolean as a string with true/false or as a number representation
 */
String toString(bool boolean, bool asNum = false);

struct StringView;

/**@brief A container for strings*/
struct String
{
public:
    /**@brief A constructor for a empty string*/
    String();
    /**@brief A constructor for a string out of a String
     * @param[in] string
     */
    String(const String& string);
    /**@brief A constructor for a string out of a std::string
     * @param[in] string
     */
    String(const std::string& string);
    /**@brief A constructor for a string out of a c style string
     * @param[in] string
     */
    String(const char* string);
    /**@brief Deconstruct the string and sets all values to 0*/
    ~String();

    /**@brief Adds a String to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(const String& string);
    /**@brief Adds a std::string to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(const std::string& string);
    /**@brief Adds a c style string to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(const char* string);
    /**@brief Adds a i8 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(i8 integer);
    /**@brief Adds a i16 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(i16 integer);
    /**@brief Adds a i32 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(i32 integer);
    /**@brief Adds a i64 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(i64 integer);
    /**@brief Adds a ui8 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(ui8 integer);
    /**@brief Adds a ui16 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(ui16 integer);
    /**@brief Adds a ui32 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(ui32 integer);
    /**@brief Adds a ui64 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(ui64 integer);
    /**@brief Adds a f32 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(f32 f);
    /**@brief Adds a f43 to the actual string
     * @param[in] string
     * @returns
     * VOID
     */
    void add(f64 f);
    /**@brief Adds a bool to the actual string. As a number or a string representation
     * @param[in] string
     * @returns
     * VOID
     */
    void add(bool boolean, bool asNum = false);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const String& string, const String& rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const String& string, const std::string& rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const String& string, const char* rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const std::string& string, const String& rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const std::string& string, const std::string& rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const std::string& string, const char* rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const char* string, const String& rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const char* string, const std::string& rString);
    /**@brief Replaced all words/sequences with the new string
     * @param[in] string
     * @param[in] rString
     * @returns
     * VOID
     */
    void replaceWith(const char* string, const char* rString);
    /**@brief Replaces the string between two positions with the new string
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * VOID
     */
    void replaceWith(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    /**@brief Replaces the string between two positions with the new string
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * VOID
     */
    void replaceWith(const ui64& posBegin, const ui64& posEnd, const String& string);
    /**@brief Replaces the string between two positions with the new string
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * VOID
     */
    void replaceWith(const ui64& posBegin, const ui64& posEnd, const char* string);

    /**@brief Inserts a String at the position
     * @param[in] pos
     * @param[in] string
     * @returns
     * VOID
     */
    void insert(const ui64& pos, const String& string);
    /**@brief Inserts a std::string at the position
     * @param[in] pos
     * @param[in] string
     * @returns
     * VOID
     */
    void insert(const ui64& pos, const std::string& string);
    /**@brief Inserts a c style string at the position
     * @param[in] pos
     * @param[in] string
     * @returns
     * VOID
     */
    void insert(const ui64& pos, const char* string);

    /**@brief Removes the chars between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @returns
     * VOID
     */
    void remove(const ui64& posBegin, const ui64& posEnd);
    /**@brief Removes the string between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * VOID
     */
    void remove(const ui64& posBegin, const ui64& posEnd, const String& string);
    /**@brief Removes the string between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * VOID
     */
    void remove(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    /**@brief Removes the string between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * VOID
     */
    void remove(const ui64& posBegin, const ui64& posEnd, const char* string);
    /**@brief Removes all words/sequences that equals to the given string
     * @param[in] string
     * @returns
     * VOID
     */
    void remove(const String& string);
    /**@brief Removes all words/sequences that equals to the given string
     * @param[in] string
     * @returns
     * VOID
     */
    void remove(const std::string& string);
    /**@brief Removes all words/sequences that equals to the given string
     * @param[in] string
     * @returns
     * VOID
     */
    void remove(const char* string);

     /**@brief Changed all chars to upper
      * @returns
      * VOID
      */
    void toUpper();
    /**@brief Changed all chars between posBegin and posEnd to upper
      * @param[in] posBegin
      * @param[in] posEnd
      * @returns
      * VOID
      */
    void toUpper(const ui64& posBegin, const ui64& posEnd);
    /**@brief Changed all chars/words/sequences between posBegin and posEnd to upper
      * @param[in] posBegin
      * @param[in] posEnd
      * @param[in] string
      * @returns
      * VOID
      */
    void toUpper(const ui64& posBegin, const ui64& posEnd, const String& string);
    /**@brief Changed all chars/words/sequences between posBegin and posEnd to upper
      * @param[in] posBegin
      * @param[in] posEnd
      * @param[in] string
      * @returns
      * VOID
      */
    void toUpper(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    /**@brief Changed all chars/words/sequences between posBegin and posEnd to upper
      * @param[in] posBegin
      * @param[in] posEnd
      * @param[in] string
      * @returns
      * VOID
      */
    void toUpper(const ui64& posBegin, const ui64& posEnd, const char* string);
    /**@brief Changed all chars/words/sequences to upper
      * @param[in] string
      * @returns
      * VOID
      */
    void toUpper(const String& string);
    /**@brief Changed all chars/words/sequences to upper
      * @param[in] string
      * @returns
      * VOID
      */
    void toUpper(const std::string& string);
    /**@brief Changed all chars/words/sequences to upper
      * @param[in] string
      * @returns
      * VOID
      */
    void toUpper(const char* string);

    /**@brief Changed all chars to lower
     * @returns
     * VOID
     */
    void toLower();
    /**@brief Changed all chars between posBegin and posEnd to lower
      * @param[in] posBegin
      * @param[in] posEnd
      * @returns
      * VOID
      */
    void toLower(const ui64& posBegin, const ui64& posEnd);
    /**@brief Changed all chars/words/sequences between posBegin and posEnd to lower
      * @param[in] posBegin
      * @param[in] posEnd
      * @param[in] string
      * @returns
      * VOID
      */
    void toLower(const ui64& posBegin, const ui64& posEnd, const String& string);
    /**@brief Changed all chars/words/sequences between posBegin and posEnd to lower
      * @param[in] posBegin
      * @param[in] posEnd
      * @param[in] string
      * @returns
      * VOID
      */
    void toLower(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    /**@brief Changed all chars/words/sequences between posBegin and posEnd to lower
      * @param[in] posBegin
      * @param[in] posEnd
      * @param[in] string
      * @returns
      * VOID
      */
    void toLower(const ui64& posBegin, const ui64& posEnd, const char* string);
    /**@brief Changed all chars/words/sequences to lower
      * @param[in] string
      * @returns
      * VOID
      */
    void toLower(const String& string);
    /**@brief Changed all chars/words/sequences to lower
      * @param[in] string
      * @returns
      * VOID
      */
    void toLower(const std::string& string);
    /**@brief Changed all chars/words/sequences to lower
      * @param[in] string
      * @returns
      * VOID
      */
    void toLower(const char* string);

    /**@brief Finds all matching in the string
     * @param[in] string
     * @returns
     * Returns a std::vector<ui64> with the starting position of the match
     */
    const std::vector<ui64> find(const String& string) const;
    /**@brief Finds all matching in the string
     * @param[in] string
     * @returns
     * Returns a std::vector<ui64> with the starting position of the match
     */
    const std::vector<ui64> find(const std::string& string) const;
    /**@brief Finds all matching in the string
     * @param[in] string
     * @returns
     * Returns a std::vector<ui64> with the starting position of the match
     */
    const std::vector<ui64> find(const char* string) const;
    /**@brief Finds all matching in the string between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * Returns a std::vector<ui64> with the starting position of the match
     */
    const std::vector<ui64> find(const ui64& posBegin, const ui64& posEnd, const String& string) const;
    /**@brief Finds all matching in the string between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * Returns a std::vector<ui64> with the starting position of the match
     */
    const std::vector<ui64> find(const ui64& posBegin, const ui64& posEnd, const std::string& string) const;
    /**@brief Finds all matching in the string between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     * @returns
     * Returns a std::vector<ui64> with the starting position of the match
     */
    const std::vector<ui64> find(const ui64& posBegin, const ui64& posEnd, const char* string) const;

    /**@brief Gets the position of the first match
     * @param[in] string
     * @returns
     * Returns a ui64 of the first match from the string
     */
    ui64 findFirst(const String& string) const;
    /**@brief Gets the position of the first match
     * @param[in] string
     * @returns
     * Returns a ui64 of the first match from the string
     */
    ui64 findFirst(const std::string& string) const;
    /**@brief Gets the position of the first match
     * @param[in] string
     * @returns
     * Returns a ui64 of the first match from the string
     */
    ui64 findFirst(const char* string) const;

    /**@brief Seperated the string in to lines
     * @returns
     * Returns a std::vector<ui64> filled with lines
     */
    std::vector<String> toLines() const;

    /**@brief Creates a string view between posBegin and posEnd
     * @param[in] posBegin
     * @param[in] posEnd
     * @returns
     * Returns a StringView between posBegin and posEnd
     */
    StringView createStringView(const ui64& posBegin, const ui64& posEnd) const;

    /**@brief Reserves more space for the string in bytes
     * @param[in] size
     * @retval TRUE if the allocation was successful
     * @retval FALSE if the allocation was not successful
     */
    const bool reserve(const ui64& size);
    /**@brief Clears the buffer und sets all values to 0 except the capacity
     * @returns
     * VOID
     */
    void clear();
    /**@brief Initialized all values. Use this in case no constructor was called
     * @returns
     * VOID
     */
    void initialize();

    /**@brief Gets the capacity
     * @returns
     * Returns the actual capacity of the string
     */
    const ui64& capacity() const;
    /**@brief Gets the length
     * @returns
     * Returns the actual length of the string
     */
    const ui64& length() const;
    /**@brief Checks if the string is empty
     * @retval TRUE if the string is empty
     * @retval FALSE if the string is not empty
     */
    bool empty() const;
    /**@brief Gets data of the string
     * @returns
     * Returns a ui8* to the data of the string
     */
    ui8* getSource() const;
    /**@brief Gets data of the string as a c style string
     * @returns
     * Returns a const char* to the data of the string
     */
    const char* c_str() const;
    /**@brief Gets the char at the index position
     * @returns
     * Returns the address of the string at the given index
     */
    const ui8& at(const ui64& index) const;

    /**@brief Clears the string and assigns the new string to the actual
     * @param[in] string
     * @returns
     * Returns a string reference to the actual string with the data of the new given string
     */
    String& operator=(const String& string);
    /**@brief Clears the string and assigns the new string to the actual
     * @param[in] string
     * @returns
     * Returns a string reference to the actual string with the data of the new given string
     */
    String& operator=(const std::string& string);
    /**@brief Clears the string and assigns the new string to the actual
     * @param[in] string
     * @returns
     * Returns a string reference to the actual string with the data of the new given string
     */
    String& operator=(const char* string);

    /**@brief Combines the actual string and a new string to a new string
     * @param[in] string
     * @returns
     * Returns a new string from the actual string and a new given string
     */
    String operator+(const String& string);
    /**@brief Combines the actual string and a new string to a new string
     * @param[in] string
     * @returns
     * Returns a new string from the actual string and a new given string
     */
    String operator+(const std::string& string);
    /**@brief Combines the actual string and a new string to a new string
     * @param[in] string
     * @returns
     * Returns a new string from the actual string and a new given string
     */
    String operator+(const char* string);

    /**@brief Adds a new string to the actual string
     * @param[in] string
     * @returns
     * Returns a string reference to the actual string and adds the data of the new given string
     */
    String& operator+=(const String& string);
    /**@brief Adds a new string to the actual string
     * @param[in] string
     * @returns
     * Returns a string reference to the actual string and adds the data of the new given string
     */
    String& operator+=(const std::string& string);
    /**@brief Adds a new string to the actual string
     * @param[in] string
     * @returns
     * Returns a string reference to the actual string and adds the data of the new given string
     */
    String& operator+=(const char* string);
private:
    bool checkCap(const ui64& size) const;
    void makeFit(const ui64& size);
private:
    ui64 mCap;
    ui64 mLen;
    ui8* mSource;
};

/**@brief Holds information of a view in a string*/
struct StringView
{
public:
    /**@brief Constructs stringview from posBegin to posEnd from the given string
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     */
    StringView(const ui64& posBegin, const ui64& posEnd, const String& string);
    /**@brief Constructs stringview from posBegin to posEnd from the given string
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     */
    StringView(const ui64& posBegin, const ui64& posEnd, const std::string& string);
    /**@brief Constructs stringview from posBegin to posEnd from the given string
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     */
    StringView(const ui64& posBegin, const ui64& posEnd, const char* string);
    /**@brief Constructs stringview from posBegin to posEnd from the given stringview
     * @param[in] posBegin
     * @param[in] posEnd
     * @param[in] string
     */
    StringView(const ui64& posBegin, const ui64& posEnd, const StringView& string);
    /**@brief Deconstructs the stringview and sets all values to 0*/
    ~StringView();

    /**@brief Constructs stringview from posBegin to posEnd from the given string
     * @returns
     * Returns the length of the stringview
     */
    const ui64& length() const;
    /**@brief Gets the view
     * @returns
     * Returns a const ui8* to the view
     */
    const ui8* getView() const;
private:
    ui64 mLen;
    ui8* mSource;
};
#endif //PLAYGROUNDLIB_STRING_H