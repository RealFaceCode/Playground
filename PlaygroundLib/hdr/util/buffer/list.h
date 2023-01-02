#ifndef PLAYGROUNDLIB_LIST_H
#define PLAYGROUNDLIB_LIST_H
#include "../../core.h"
#include "iterator.h"
#include "../memory.h"
#include <initializer_list>

template<typename Type>
struct List
{
public:
    List();
    List(const ui64& elements);
    List(const List& other);
    List(const List&& other) noexcept ;
    ~List();

    void add(const Type& element);
    void add(const Type* element, const ui64& elements);
    void add(const List<Type>& list);
    void add(const std::initializer_list<Type>& list);
    void remove(const ui64& index);
    void remove(const ui64& begin, const ui64& end);

    Type* at(const ui64& index);

    Iterator<Type> begin();
    Iterator<Type> end();

    Iterator_R<Type> rBegin();
    Iterator_R<Type> rEnd();

    Type* source();
    const ui64& length();
    const ui64& capacity();

    bool reserve(const ui64& elements);
    void clear();
    void destroy();

    Type* operator[](const ui64& index);
    bool operator==(const List<Type>& list);
    List<Type>& operator=(const List<Type>& list);
    List<Type>& operator=(const std::initializer_list<Type>& list);
    List<Type>& operator+=(const Type& element);
    List<Type>& operator+=(const List<Type>& list);
    List<Type>& operator+=(const std::initializer_list<Type>& list);
private:
    void makeFit(const ui64& elements);
    void callDeconstObj();
    const Type* at_c(const ui64 index) const;
private:
    ui64 mLength;
    ui64 mCap;
    Type* mSource;
private:
    ui64 TypeSize;
};

template<typename Type>
List<Type>::List()
    : mLength(0), mCap(0), mSource(0), TypeSize(sizeof(Type)) {}

template<typename Type>
List<Type>::List(const ui64 &elements)
    : mLength(0), mCap(elements), mSource(0), TypeSize(sizeof(Type))
{
    makeFit(elements);
}

template<typename Type>
List<Type>::List(const List<Type>& other)
    : List()
{
    *this = other;
}

template<typename Type>
List<Type>::List(const List<Type>&& other) noexcept
    : List()
{
    *this = std::move(other);
}

template<typename Type>
List<Type>::~List()
{
    destroy();
}

template<typename Type>
void List<Type>::add(const Type &element)
{
    makeFit(1);
    mSource[mLength] = element;
    mLength += 1;
}

template<typename Type>
void List<Type>::add(const Type *element, const ui64 &elements)
{
    makeFit(elements);
    for(ui64 i = 0; i < elements; i++)
    {
        add(element[i]);
    }
}

template<typename Type>
void List<Type>::add(const List<Type> &list)
{
    makeFit(list.mLength);
    for(ui64 i = 0; i < list.mLength; i++)
    {
        add(*list.at_c(i));
    }
}

template<typename Type>
void List<Type>::add(const std::initializer_list<Type>& list)
{
    add(data(list), list.size());
}

template<typename Type>
void List<Type>::remove(const ui64 &index)
{
    if(index >= mLength)
    {
        return;
    }
    memmove(mSource + index, mSource + index + 1 , (mLength - index - 1) * TypeSize);
    mLength -= 1;
}

template<typename Type>
void List<Type>::remove(const ui64 &begin, const ui64 &end)
{
    if(begin >=mLength || end >= mLength || begin > end)
    {
        return;
    }
    ui64 len = end - begin;
    memmove(mSource + begin, mSource + end + 1, (mLength - len - 1) * TypeSize);
    mLength -= len + 1;
}

template<typename Type>
Type *List<Type>::at(const ui64 &index)
{
    if(index >= mLength)
    {
        return nullptr;
    }
    return &mSource[index];
}

template<typename Type>
Iterator<Type> List<Type>::begin()
{
    return Iterator<Type>(mSource, mLength).begin();
}

template<typename Type>
Iterator<Type> List<Type>::end()
{
    return Iterator<Type>(mSource, mLength).end();
}

template<typename Type>
Iterator_R<Type> List<Type>::rBegin()
{
    return Iterator_R<Type>(mSource, mLength).begin();
}

template<typename Type>
Iterator_R<Type> List<Type>::rEnd()
{
    return Iterator_R<Type>(mSource, mLength).end();
}

template<typename Type>
Type *List<Type>::source()
{
    return mSource;
}

template<typename Type>
const ui64 &List<Type>::length()
{
    return mLength;
}

template<typename Type>
const ui64 &List<Type>::capacity()
{
    return mCap;
}

template<typename Type>
bool List<Type>::reserve(const ui64 &elements)
{
    ui64 bytesAdd = elements * TypeSize;
    if(!mSource)
    {
        mSource = (Type*)Malloc(bytesAdd);
    }
    else
    {
        ui64 bytesBuffer = mCap * TypeSize;
        mSource = (Type*) Realloc_s(mSource, bytesBuffer, bytesAdd);
    }
    if(mSource)
    {
        mCap += elements;
        return true;
    }
    return false;
}

template<typename Type>
void List<Type>::clear()
{
    mLength = 0;
}

template<typename Type>
void List<Type>::destroy()
{
    if(mSource)
    {
        callDeconstObj();
        Free(mSource);
    }
    mSource = nullptr;
    mLength = 0;
    mCap = 0;
}

template<typename Type>
Type *List<Type>::operator[](const ui64 &index)
{
    return at(index);
}

template<typename Type>
List<Type> &List<Type>::operator=(const List<Type> &list)
{
    TypeSize = list.TypeSize;
    destroy();
    add(list);
    return *this;
}

template<typename Type>
List<Type> &List<Type>::operator=(const std::initializer_list<Type> &list)
{
    destroy();
    add(data(list), list.size());
    return *this;
}

template<typename Type>
List<Type> &List<Type>::operator+=(const Type &element)
{
    add(element);
    return *this;
}

template<typename Type>
List<Type> &List<Type>::operator+=(const List<Type> &list)
{
    add(list);
    return *this;
}

template<typename Type>
bool List<Type>::operator==(const List<Type> &list)
{
    return false;
}

template<typename Type>
void List<Type>::makeFit(const ui64 &elements)
{
    if((mLength + elements) > mCap)
    {
        reserve((mCap - mLength) + elements);
    }
}

template<typename Type>
List<Type> &List<Type>::operator+=(const std::initializer_list<Type> &list)
{
    add(list);
    return *this;
}

template<typename Type>
void List<Type>::callDeconstObj()
{
    for(ui64 i = 0; i < mLength; i++)
    {
        mSource[i].~Type();
    }
}

template<typename Type>
const Type *List<Type>::at_c(const ui64 index) const
{
    return &mSource[index];
}

#endif //PLAYGROUNDLIB_LIST_H