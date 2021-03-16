#pragma once
#ifndef Table_CONST_H_INCLUDED
#define Table_CONST_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include "Exception.h"

using namespace std;

template <typename Type> class Table_const
{
private:
    vector<Type> table;

public:
    Table_const(string filename) 
    {
        ifstream fs(filename.c_str(), ios::in);
        if (!fs.is_open())
            throw Exception("Unable to open file " + filename);
        Type elem;
        while (!fs.eof())
        {
            fs >> elem;
            add(elem);
        }
    }

    ~Table_const()
    {
        table.clear();
    }

    inline void add(Type elem)
    {
        table.push_back(elem);
    }


    bool is_contains(Type elem)
    {
        typename vector<Type>::iterator it = find(table.begin(), table.end(), elem);
        if (it == table.end())
            throw Exception("Element doesn't contains");
        return true;
    }


    bool get_val(int num, Type& elem)
    {
        if (num < 0 || num >= table.size())
            throw Exception("Element with this num doesn't contains");
        typename vector<Type>::iterator it = table.begin();
        for (int i = 0; i < num; i++)
            it++;
        elem = *it;
        return true;
    }


    bool get_num(Type elem, int& num)
    {
        if (!is_contains(elem))
            throw Exception("This element doesn't contains");
        
        auto it = find(table.begin(), table.end(), elem);
        num = it - table.begin();
        return true;
    }


    void output(string filename)
    {
        ofstream fout(filename);
        fout << "i     name" << endl;
        for (size_t i = 0; i < table.size(); i++)
        {
            fout << i;
            fout << "    " << table[i] << endl;
        }

        fout.close();
    }
};

#endif 
