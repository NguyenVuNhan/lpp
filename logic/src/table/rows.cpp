#include "rows.h"
#include "../notation/variable.h"
#include "../notation/negate.h"
#include "../notation/and.h"
#include "../utils.h"

Rows::Rows(uintmax_t elem, bool value)
{
    this->elem_byte = elem;
    this->elem_str = toHexString(elem);
    this->value = value;
}

Node *Rows::toNode(list<string> label)
{
    list<string>::iterator l_it = label.begin();
    string::iterator e_it = elem_str.begin();
    Node *left = nullptr,
         *right = nullptr;
    do
    {
        Node *newNode = nullptr;
        switch(*e_it)
        {
        case '1':
        {
            newNode = new Variable(*l_it);
            break;
        }
        case '0':
        {
            newNode = new Negate(new Variable(*l_it));
            break;
        }
        }

        if(left == nullptr)
            left = newNode;
        else
            right = newNode;

        if(left != nullptr && right != nullptr)
        {
            left = new And(left, right);
            right = nullptr;
        }
    }
    while(++l_it != label.end() && ++e_it != elem_str.end());

    return left;
}

int Rows::is_match_pair(const Rows &other)
{
    if(value == other.value)
    {
        int pos = -1;
        string::iterator it = elem_str.begin();
        string::const_iterator o_it = other.elem_str.begin();
        for (;it != elem_str.end() && o_it != other.elem_str.begin(); ++it, ++o_it)
            if(*it != *o_it)
            {
                if(pos == -1)
                    pos = static_cast<int>(distance(elem_str.begin(), it));
                else
                    return -1;
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
