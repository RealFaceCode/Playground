#ifndef PLAYGROUNDLIB_MAP_H
#define PLAYGROUNDLIB_MAP_H
#include "../../core.h"
#include "pair.h"
#include "iterator.h"

template<typename Key, typename Value>
struct Map
{
public:
    void add(const Key& key);
    void add(const Key& key, const Value& value);

    bool contains(const Key& key);
    Pair<Key, Value>* find(const Key& key);

    Iterator<Pair<Key, Value>> begin();
    Iterator<Pair<Key, Value>> end();

    Value& operator[](const Key& key);
private:
    std::vector<Pair<Key, Value>> mEntries;
};

template<typename Key, typename Value>
void Map<Key, Value>::add(const Key& key)
{
    if(contains(key))
    {
        return;
    }
    mEntries.template emplace_back(Pair<Key, Value>{key, Value()});
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
    mEntries.template emplace_back(Pair<Key, Value>{key, value});
}

template<typename Key, typename Value>
bool Map<Key, Value>::contains(const Key& key)
{
    auto* p = find(key);
    if(p)
    {
        return true;
    }
    return false;
}

template<typename Key, typename Value>
Pair<Key, Value>* Map<Key, Value>::find(const Key& key)
{
    for(Pair<Key, Value>& p : mEntries)
    {
        if(p.first == key)
        {
            return &p;
        }
    }
    return nullptr;
}

template<typename Key, typename Value>
Iterator<Pair<Key, Value>> Map<Key, Value>::begin()
{
    return Iterator<Pair<Key, Value>>(mEntries.begin().base(), mEntries.size());
}

template<typename Key, typename Value>
Iterator<Pair<Key, Value>> Map<Key, Value>::end()
{
    return Iterator<Pair<Key, Value>>(mEntries.begin().base(), mEntries.size());
}

template<typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key& key)
{
    auto* p = find(key);
    if(p)
    {
        return (Value&)p->second;
    }
    add(key);
    return mEntries.at(mEntries.size() - 1).second;
}
#endif //PLAYGROUNDLIB_MAP_H