#pragma once

#include "Lexeme.h"
#include <vector>

using namespace std;


const int hash_N = 26 * 2 + 10; //Максимальное значение хэша
class Table_var {
public:

	Table_var() {
		our_table = new vector<Lexeme>[hash_N];
	}

	~Table_var() {
		for (int i = 0; i < hash_N; i++)
			our_table[i].clear();

		delete[] our_table;
	}

	bool add_lexeme(Lexeme lexeme); //Функция добавления идендификатора, true - если добавили, false - не добавили.
	bool set_type(string ind_name, int type); //Функция добавления значения типа индендификатору.
	bool set_value(string ind_name, int val); //Функция  измения идентификатора.
	bool set_type(int hash, int numb, int type); //Установка типа по полному адресу
	bool set_value(int hash, int numb, bool val); //Установка значения по полному адресу
	bool set_name(int hash, int numb, string name);
	bool is_contains(string ind_name); //Проверка, входит ли идендификатор в таблицу, true - входит, false - нет.
	bool get_location(string ind_name, int& hash, int& numb); //Возврашает полный адрес идентификатора, либо false если его нет в таблице.
	bool get_lexeme(string ind_name, Lexeme& gets_lexeme); //Получаем токен по идентификатору, если такого нет - false.
	bool get_lexeme(int hash, int numb, Lexeme& gets_lexeme); //Получаем токен по его полному адресу, если такого нет - false.



private:

	vector<Lexeme>* our_table; 


	int calc_hash(string ind_name);	
	int find_in_vector(int hash, string ind_name);
};