#pragma once

#include "Exception.h"
#include <set>

using namespace std;

struct function {
	int argc; // Количество аргументов
	set <pair<string, bool>> argc ; // Тип аргументов и способ их передачи
	int type; // Возвращаемое значение (0 - есть, 1 - int)

	// хз чё с этим делать, но думаю, что вот что-то подобное должно быть
};


class Lexeme {
public:
	string name; 
	int type; //Тип идентификатор (0 - int, 1 - функция)
	int value; // Инциализирован ли идентификатор ()


	Lexeme(string id_name) {
		name = id_name;
		type = 0;
		value = false;
	}


	bool operator < (const Lexeme& b) {
		return name < b.name;
	}


	bool operator == (Lexeme b) {
		return name == b.name;
	}
};