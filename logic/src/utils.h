#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <list>
#include <iomanip>
#include <list>

using namespace std;

template<class T>
bool deleteAll(T *e)
{
    delete e;
    e = nullptr;
    return true;
}

template<typename T = string>
bool contains(list<T> &listOfElements, const T &element)
{
    auto it = find(listOfElements.begin(), listOfElements.end(), element);
    return it != listOfElements.end();
}

template<class T>
void listReplaceAt(list<T *> &mainList, list<T *> &tmpList, long pos)
{
    auto it = next(mainList.begin(), pos);
    it = mainList.erase(it);
    mainList.splice(it, tmpList);
}

template<class TBase, class TDerrived>
void listReplaceAt(list<TBase *> &mainList, TDerrived* tmpElem, long pos)
{
    auto it = next(mainList.begin(), pos);
    it = mainList.erase(it);
    mainList.insert(it, tmpElem);
}

template<class T>
list<T *> copyList(list<T *> &other)
{
    list<T *> tmpList;
    for(T *e : other)
    {
        tmpList.push_back(e->copy());
    }
    return tmpList;
}

static bool isContain(string mainStr, string containedStr)
{
    return mainStr.find(containedStr) != string::npos;
}

static bool isContain(string mainStr, char containedChar)
{
    return mainStr.find(containedChar) != string::npos;
}

static string getUniqueString(string str)
{
    string tmp;
    for(auto c : str)
        if(!isContain(tmp, c))
            tmp += c;
    return tmp;
}
#endif // UTILS_H
