#ifndef PLAYGROUNDLIB_MAP_H
#define PLAYGROUNDLIB_MAP_H
#include "../../core.h"
#include "pair.h"
#include "iterator.h"
#include "list.h"

template<typename Key, typename Value>
struct Map
{
public:
    void add(const Key& key);
    void add(const Key& key, const Value& value);

    bool contains(const Key& key) const;
    Pair<Key, Value>* find(const Key& key) const;

    Iterator<Pair<Key, Value>> begin() const;
    Iterator<Pair<Key, Value>> end() const;

    Value& operator[](const Key& key);
private:
    List<Pair<Key, Value>> mEntries;
};

template<typename Key, typename Value>
void Map<Key, Value>::add(const Key& key)
{
    if(contains(key))
    {
        return;
    }
    mEntries.add(Pair<Key, Value>{key, Value()});
}

template<typename Key, typename Value>
void Map<Key, Value>::add(const Key& key, const Value&  value)
{
    auto* p = find(key);
    if(p)
    {
        p->second = value;
        return;
    }
    mEntries.add(Pair<Key, Value>{key, value});
}

template<typename Key, typename Value>
bool Map<Key, Value>::contains(const Key& key) const
{
    auto* p = find(key);
    if(p)
    {
        return true;
    }
    return false;
}

template<typename Key, typename Value>
Pair<Key, Value>* Map<Key, Value>::find(const Key& key) const
{
    for(auto& p : mEntries)
    {
        if(p.first == key)
        {
            return (Pair<Key, Value>*)&p;
        }
    }
    return nullptr;
}

template<typename Key, typename Value>
Iterator<Pair<Key, Value>> Map<Key, Value>::begin() const
{
    return mEntries.begin();
}

template<typename Key, typename Value>
Iterator<Pair<Key, Value>> Map<Key, Value>::end() const
{
    return mEntries.end();
}

template<typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key& key)
{
    auto* p = find(key);
    if(p)
    {
        return (Value&)p->second;
    }
    add(key, Value());
    return (Value&)mEntries.at(mEntries.length() - 1)->second;
}
#endif //PLAYGROUNDLIB_MAP_H