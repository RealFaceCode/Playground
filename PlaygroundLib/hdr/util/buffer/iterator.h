#ifndef PLAYGROUNDLIB_ITERATOR_H
#define PLAYGROUNDLIB_ITERATOR_H
#include "../../core.h"

template<typename Value>
class Iterator {
public:
    Iterator(Value* value);
    Iterator(Value* value, const ui64& length);

    Iterator begin();
    Iterator end();

    bool operator!= (const Iterator& itr);
    Iterator operator++();
    const Value& operator*();
private:
    Value* mPtr;
    uint64_t mLength;
};

template<typename Value>
Iterator<Value>::Iterator(Value *value)
: mPtr(value), mLength(0) {}

template<typename Value>
Iterator<Value>::Iterator(Value* value, const ui64& length)
: mPtr(value), mLength(length){}

template<typename Value>
Iterator<Value> Iterator<Value>::begin()
{
    return Iterator(mPtr, mLength);
}

template<typename Value>
Iterator<Value> Iterator<Value>::end()
{
    return Iterator(mPtr + mLength);
}

template<typename Value>
bool Iterator<Value>::operator!=(const Iterator &itr)
{
    return mPtr != itr.mPtr + itr.mLength;
}

template<typename Value>
Iterator<Value> Iterator<Value>::operator++()
{
    ++mPtr;
    return *this;
}

template<typename Value>
const Value& Iterator<Value>::operator*()
{
    return *mPtr;
}
#endif //PLAYGROUNDLIB_ITERATOR_H
