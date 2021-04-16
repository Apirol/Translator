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
    Table_const() { }

    ~Table_const()
    {
        table.clear();
    }

    
    bool read(string name)
    {
        ifstream fs(name.c_str(), ios::in);
        if (!fs.is_open()) return false;
        Type elem;
        while (!fs.eof())
        {
            fs >> elem;
            add(elem);
        }
        return true;
    }

    inline void add(Type elem)
    {
        table.push_back(elem);
    }


    bool is_contains(Type elem)
    {
        typename vector<Type>::iterator it = find(table.begin(), table.end(), elem);
        if (it == table.end())
            return false;
        return true;
    }


    bool get_val(int num, Type& elem)
    {
        if (num < 0 || num >= table.size())
            return false;
        typename vector<Type>::iterator it = table.begin();
        for (int i = 0; i < num; i++)
            it++;
        elem = *it;
        return true;
    }


    bool get_num(Type elem, int& num)
    {
        if (!is_contains(elem))
            return false;
        
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
