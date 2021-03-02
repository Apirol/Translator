#pragma once
#ifndef Table_CONST_H_INCLUDED
#define Table_CONST_H_INCLUDED

#include <fstream>
#include <string>
#include <set>
#include "Exception.h"

using namespace std;

template <typename Type> class Table_const
{
private:
    set<Type> Table;

public:
    Table_const(string filename) 
    {
        ifstream fs(filename.c_str(), ios::in);
        if (!fs.is_open())
            throw Exception("Unable to open file");
        Type elem;
        while (!fs.eof())
        {
            fs >> elem;
            add(elem);
        }
    }

    ~Table_const()
    {
        Table.clear();
    }

    inline void add(Type elem)
    {
        Table.insert(elem);
    }

    bool is_contains(Type elem);
    bool get_num(Type elem, int &num);
    bool get_val(int num, Type &elem);
};

#endif 
