#include "rows.h"
#include "../notation/variable.h"
#include "../notation/negate.h"
#include "../notation/multiand.h"
#include "../utils.h"

string Rows::toBinString(uintmax_t i, uintmax_t strLen)
{
    string bin;
    uintmax_t mask = 1;
    for(uintmax_t j = 0; j < strLen; j++)
    {
        if((mask&i) >= 1)
            bin = '1' + bin;
        else
            bin = '0' + bin;
        mask <<= 1;
    }
    return bin;
}

Rows::Rows(uintmax_t elem, bool value, uintmax_t strLen)
{
    this->elem_byte = elem;
    this->elem_str = toBinString(elem, strLen);
    this->value = value;
}

shared_ptr<Node> Rows::toNode(list<string> label)
{
    list<shared_ptr<Node> > tmpList;

    for(uint i = 0; i < elem_str.size(); i++)
    {
        char val = elem_str[i];
        if(val != 'x')
        {
            if(val == '0')
            {
                tmpList.push_back(make_shared<Negate>(make_shared<Variable>(*next(label.begin(), i))));
            }
            else
            {
                tmpList.push_back(make_shared<Variable>(*next(label.begin(), i)));
            }
        }

    }

    return make_shared<MultiAndNorm>(tmpList);
}

int Rows::is_match_pair(const Rows &other)
{
    if(value == other.value)
    {
        int pos = -1;
        for (uint i = 0; i < this->elem_str.size(); i++)
        {
            if(elem_str[i] != other.elem_str[i])
            {
                if(pos == -1)
                {
                    pos = static_cast<int>(i);
                }
                else
                {
                    return -1;
                }
            }
        }
        return pos;
    }
    return -1;
}

bool Rows::getValue()
{
    return value;
}

void Rows::setDontCare(uint pos)
{
    elem_str.replace(pos, 1, "x");
}

string Rows::getElem()
{
    return elem_str;
}

string Rows::toString()
{
    string tmpString = "";
    for(char c : elem_str)
    {
        tmpString += c;
        tmpString += ' ';
    }
    tmpString += value ? '1' : '0';
    return tmpString;
}

void Rows::operator=(const Rows &other)
{
    this->elem_str = other.elem_str;
    this->value = other.value;
    this->checked = true;
}

bool Rows::operator==(const Rows &other)
{
    return this->value == other.value && this->elem_str == other.elem_str;
}

bool Rows::operator<(const Rows &other)
{
    return this->elem_byte < other.elem_byte;
}
