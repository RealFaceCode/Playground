#ifndef PLAYGROUNDLIB_PAIR_H
#define PLAYGROUNDLIB_PAIR_H
template<typename First, typename Second>
struct Pair
{
public:
    Pair() = default;
    Pair(const First& first, const Second& second);

    First first;
    Second second;
};

template<typename First, typename Second>
Pair<First, Second>::Pair(const First &first, const Second &second)
{
    this->first = first;
    this->second = second;
}
#endif //PLAYGROUNDLIB_PAIR_H
