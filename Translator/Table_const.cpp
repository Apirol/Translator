#include "Table_const.h"


template <typename Type>
bool Table_const<Type>::is_contains(Type elem)
{
    typename set<Type>::iterator it = Table.find(elem);
    if (it == Table.end())
        throw new Exception("Element doesn't contains");
    return true;
}


template <typename Type>
bool Table_const<Type>::get_val(int num, Type& elem)
{
    if (num < 0 || num >= Table.size())
        throw new Exception("Element with this num doesn't contains");
    typename set<Type>::iterator it = Table.begin();
    for (int i = 0; i < num; i++)
        it++;
    elem = *it;
    return true;
}


template <typename Type>
bool Table_const<Type>::get_num(Type elem, int &num)
{
    if (!contains(elem))
        throw new Exception("This element doesn't contains");
    num = distance(Table.begin(), Table.find(elem));
    return true;
}