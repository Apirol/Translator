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

	bool add_ind(string ind_name); //Функция добавления индендификатора, true - если добавили, false - не добавили.
	bool set_ind_type(string ind_name, int type); //Функция добавления значения типа индендификатору.
	bool set_ind_val(string ind_name, int val); //Функция  измения типо инициализации индендификатора.
	bool check_ind_in_table(string ind_name); //Проверка, входит ли индендификатор в таблицу, true - входит, false - нет.
	bool ind_adrress(string ind_name, int& hash, int& numb); //Возврашает полный адрес идентификатора, либо false если его нет в таблице.
	bool get_lexeme(string ind_name, Lexeme& gets_lexeme); //Получаем токен по идентификатору, если такого нет - false.
	bool get_lexeme(int hash, int numb, Lexeme& gets_lexeme); //Получаем токен по его полному адресу, если такого нет - false.
	bool set_type_address(int hash, int numb, int type); //Установка типа по полному адресу
	bool set_value_address(int hash, int numb, bool val); //Установка значения по полному адресу



private:

	vector<Lexeme>* our_table; //наша табличка


	int calc_hash(string ind_name);	//Функция вычисления хэша. Сначала - числа, потом строчные буквы, потом заглавные
	int find_in_vector(int hash, string ind_name);
};