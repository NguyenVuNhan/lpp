#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <list>
#include <iomanip>

using namespace std;

template<class T>
bool deleteAll(T *e)
{
    delete e;
    return true;
}

template<typename T = string>
bool contains(list<T> &listOfElements, const T &element)
{
    auto it = find(listOfElements.begin(), listOfElements.end(), element);
    return it != listOfElements.end();
}

template<class T>
void listReplaceAt(list<T> &mainList, list<T> &tmpList, long pos)
{
    auto it = next(mainList.begin(), pos);
    mainList.erase(it);
    mainList.splice(it, tmpList);
}

template<class TBase, class TDerrived>
void listReplaceAt(list<TBase> &mainList, TDerrived tmpElem, long pos)
{
    auto it = next(mainList.begin(), pos);
    mainList.erase(it);
    mainList.insert(it, tmpElem);
}

template<typename T>
string toHexString(T i )
{
    stringstream stream;
    stream << hex << i;
    return stream.str();
}
#endif // UTILS_H
