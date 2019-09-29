#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <list>
#include <iomanip>
#include <list>
#include <memory>

using namespace std;

template<typename T = string>
bool contains(list<T> &listOfElements, const T &element)
{
    auto it = find(listOfElements.begin(), listOfElements.end(), element);
    return it != listOfElements.end();
}

template<typename T>
void listReplaceAt(list<shared_ptr<T> > &mainList, list<shared_ptr<T>> &tmpList, long pos)
{
    auto it = next(mainList.begin(), pos);
    it = mainList.erase(it);
    mainList.splice(it, tmpList);
}

template<typename T>
void listReplaceAt(list<shared_ptr<T> > &mainList, shared_ptr<T> tmpElem, long pos)
{
    auto it = next(mainList.begin(), pos);
    it = mainList.erase(it);
    mainList.insert(it, tmpElem);
}

template<class T>
list<shared_ptr<T>> copyList(list<shared_ptr<T>> &other)
{
    list<shared_ptr<T>> tmpList;
    for(auto e : other)
    {
        tmpList.push_back(e);
    }
    return tmpList;
}

template<typename T>
T readList(list<T> l1, uint pos)
{
    auto it = next(l1.begin(), pos);
    return *it;
}

static bool isContain(string mainStr, string containedStr)
{
    return mainStr.find(containedStr) != string::npos;
}

static bool isContain(string mainStr, char containedChar)
{
    return mainStr.find(containedChar) != string::npos;
}

static bool isContain(string mainStr, list<char> containedChar)
{
    for(auto c : mainStr)
    {
        for(auto cc : containedChar)
        {
            if(c == cc)
            {
                return true;
            }
        }
    }
    return false;
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
