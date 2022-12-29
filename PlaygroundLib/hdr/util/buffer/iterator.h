#ifndef PLAYGROUNDLIB_ITERATOR_H
#define PLAYGROUNDLIB_ITERATOR_H
#include "../../core.h"

template<typename Type>
struct Iterator
{
public:
    Iterator(Type* element);
    Iterator(Type* element, const ui64& length);

    virtual Type* begin();
    virtual Type* end();

    bool operator== (const Iterator& itr);
    bool operator!= (const Iterator& itr);
    virtual Iterator& operator++();
    virtual const Iterator<Type> operator++(int);
    virtual Iterator& operator--();
    virtual const Iterator<Type> operator--(int);
    const Type& operator*();
    virtual Iterator& operator+(const ui64& length);
    virtual Iterator& operator-(const ui64& length);
protected:
    Type* mPtr;
    ui64 mLength;
};

template<typename Type>
Iterator<Type>::Iterator(Type *element, const ui64 &length)
: mPtr(element), mLength(length) {}

template<typename Type>
Iterator<Type>::Iterator(Type *element)
: mPtr(element), mLength(0) {}

template<typename Type>
bool Iterator<Type>::operator==(const Iterator &itr)
{
    return mPtr == itr.mPtr + itr.mLength;
}

template<typename Type>
bool Iterator<Type>::operator!=(const Iterator &itr)
{
    return mPtr != itr.mPtr + itr.mLength;
}

template<typename Type>
Iterator<Type>& Iterator<Type>::operator++()
{
    mPtr++;
    return *this;
}

template<typename Type>
const Iterator<Type> Iterator<Type>::operator++(int)
{
    mPtr++;
    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator--() {
    mPtr--;
    return *this;
}

template<typename Type>
const Iterator<Type> Iterator<Type>::operator--(int)
{
    mPtr--;
    return *this;
}

template<typename Type>
const Type& Iterator<Type>::operator*()
{
    return *mPtr;
}

template<typename Type>
Type *Iterator<Type>::begin()
{
    return mPtr;
}

template<typename Type>
Type *Iterator<Type>::end() {
    return mPtr + mLength;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator+(const ui64& length)
{
    mPtr += length;
    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator-(const ui64& length)
{
    mPtr -= length;
    return *this;
}

template<typename Type>
struct Iterator_R : Iterator<Type>
{
public:
    Iterator_R(Type* element);
    Iterator_R(Type* element, const ui64& length);

    Type* begin() override;
    Type* end() override;

    Iterator<Type>& operator++() override;
    const Iterator<Type> operator++(int) override;
    Iterator<Type>& operator--() override;
    const Iterator<Type> operator--(int) override;
    Iterator<Type>& operator+(const ui64& length) override;
    Iterator<Type>& operator-(const ui64& length) override;

};

template<typename Type>
Iterator_R<Type>::Iterator_R(Type *element)
    : Iterator<Type>(element) {}

template<typename Type>
Iterator_R<Type>::Iterator_R(Type *element, const ui64 &length)
    : Iterator<Type>(element, length) {}

template<typename Type>
Type *Iterator_R<Type>::begin()
{
    return this->mPtr + this->mLength - 1;
}

template<typename Type>
Type *Iterator_R<Type>::end()
{
    return this->mPtr - 1;
}

template<typename Type>
Iterator<Type> &Iterator_R<Type>::operator++()
{
    this->mPtr--;
    return *this;
}

template<typename Type>
const Iterator<Type> Iterator_R<Type>::operator++(int)
{
    this->mPtr--;
    return *this;
}

template<typename Type>
Iterator<Type> &Iterator_R<Type>::operator--()
{
    this->mPtr++;
    return *this;
}

template<typename Type>
const Iterator<Type> Iterator_R<Type>::operator--(int)
{
    this->mPtr++;
    return *this;
}
template<typename Type>
Iterator<Type>& Iterator_R<Type>::operator+(const ui64& length)
{
    this->mPtr--;
    return *this;
}

template<typename Type>
Iterator<Type>& Iterator_R<Type>::operator-(const ui64& length)
{
    this->mPtr++;
    return *this;
}

#endif //PLAYGROUNDLIB_ITERATOR_H
