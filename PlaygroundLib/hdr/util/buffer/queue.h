#ifndef PLAYGROUNDLIB_QUEUE_H
#define PLAYGROUNDLIB_QUEUE_H
#include "../../core.h"
#include "list"
#include "iterator.h"

template<typename Type>
struct Queue
{
public:
    Queue();
    Queue(const ui64& elements);
    ~Queue();

    void push(const Type& element);
    void push(const Type* element, const ui64& elements);
    //void add(const List<Type>& list);
    void push(const std::initializer_list<Type>& list);

    Type pop();

    Iterator<Type> begin() const;
    Iterator<Type> end() const;

    Iterator_R<Type> rBegin() const;
    Iterator_R<Type> rEnd() const;

    Type* source() const;
    const ui64& length() const;
    const ui64& capacity() const;

    bool reserve(const ui64& elements);
    void clear();
    void destroy();

    Queue<Type>& operator=(const List<Type>& list);
    Queue<Type>& operator=(const std::initializer_list<Type>& list);
    Queue<Type>& operator+=(const Type& element);
    Queue<Type>& operator+=(const List<Type>& list);
    Queue<Type>& operator+=(const std::initializer_list<Type> &list);
private:
    List<Type> mSource;
};

template<typename Type>
Queue<Type>::Queue()
    : mSource(List<Type>())
{}

template<typename Type>
Queue<Type>::Queue(const ui64 &elements)
    : mSource(List<Type>(elements))
{}

template<typename Type>
Queue<Type>::~Queue()
{
    destroy();
}

template<typename Type>
void Queue<Type>::push(const Type &element)
{
    mSource.add(element);
}

template<typename Type>
void Queue<Type>::push(const Type *element, const ui64 &elements)
{
    mSource.add(element, elements);
}

template<typename Type>
void Queue<Type>::push(const std::initializer_list<Type> &list)
{
    mSource.add(list);
}

template<typename Type>
Type Queue<Type>::pop()
{
    Type* value = mSource.at(0);
    if(!value)
    {
        return Type();
    }
    Type rValue = *value;
    mSource.remove(0);
    return rValue;

}

template<typename Type>
Iterator <Type> Queue<Type>::begin() const
{
    return mSource.begin();
}

template<typename Type>
Iterator <Type> Queue<Type>::end() const
{
    return mSource.end();
}

template<typename Type>
Iterator_R <Type> Queue<Type>::rBegin() const
{
    return mSource.rBegin();
}

template<typename Type>
Iterator_R <Type> Queue<Type>::rEnd() const
{
    return mSource.rEnd();
}

template<typename Type>
Type *Queue<Type>::source() const
{
    return mSource.source();
}

template<typename Type>
const ui64 &Queue<Type>::length() const
{
    return mSource.length();
}

template<typename Type>
const ui64 &Queue<Type>::capacity() const
{
    return mSource.capacity();
}

template<typename Type>
bool Queue<Type>::reserve(const ui64 &elements)
{
    return mSource.reserve(elements);
}

template<typename Type>
void Queue<Type>::clear()
{
    mSource.clear();
}

template<typename Type>
void Queue<Type>::destroy()
{
    mSource.destroy();
}

template<typename Type>
Queue <Type> &Queue<Type>::operator=(const List<Type> &list)
{
    mSource = list;
    return *this;
}
template<typename Type>
Queue <Type> &Queue<Type>::operator=(const std::initializer_list<Type> &list)
{
    mSource = list;
    return *this;
}

template<typename Type>
Queue <Type> &Queue<Type>::operator+=(const Type &element)
{
    mSource.add(element);
    return*this;
}

template<typename Type>
Queue<Type> &Queue<Type>::operator+=(const List<Type> &list)
{
    mSource.add(list);
    return* this;
}

template<typename Type>
Queue <Type> &Queue<Type>::operator+=(const std::initializer_list<Type> &list)
{
    mSource.add(list);
    return* this;
}
#endif //PLAYGROUNDLIB_QUEUE_H
