#ifndef ROWS_H
#define ROWS_H

#include <stdint.h> // type uint16_t
#include <math.h>   // type ulong
#include "../proposition/tree.h"

class Rows
{
private:
    uintmax_t elem_byte;
    bool value;
    string toBinString(uintmax_t i, uintmax_t strLen);

public:
    string elem_str;
    bool checked = false;
    Rows(uintmax_t elem_str, bool value, uintmax_t strLen=2);
    Node *toNode(list<string> label);
    int is_match_pair(const Rows &other);
    bool getValue();
    void setDontCare(uint pos);
    string getElem();
    void operator=(const Rows &other);
    bool operator==(const Rows &other);
    bool operator<(const Rows &other);
};

#endif // ROWS_H
