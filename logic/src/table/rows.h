#ifndef ROWS_H
#define ROWS_H

#include <stdint.h> // type uint16_t
#include <math.h>   // type ulong
#include "../proposition/tree.h"

class Rows
{
private:
    uintmax_t elem_byte;
    string elem_str;
    bool value;

public:
    bool checked = false;
    Rows(uintmax_t elem_str, bool value);
    Node *toNode(list<string> label);
    int is_match_pair(const Rows &other);
    bool getValue();
    void setDontCare(uint pos);
    void operator=(const Rows &other);
    bool operator==(const Rows &other);
    bool operator<(const Rows &other);
};

#endif // ROWS_H
