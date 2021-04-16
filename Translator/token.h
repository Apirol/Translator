#pragma once
#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

// Класс токенов
class Token
{
public:
    int table; // Номер таблицы
    int place; // Положение в таблице
    int chain; // Положение в цепочке
    // Конструкторы
    Token();
    Token(int table_, int place_, int chain_);
    // Ввод-вывод токенов
    friend istream& operator >> (istream& istream_, Token& token_);
    friend ostream& operator << (ostream& ostream_, const Token& token_);
};

#endif // TOKEN_H_INCLUDED
