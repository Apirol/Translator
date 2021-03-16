#pragma once

#include "Exception.h"
#include <set>

using namespace std;


class Lexeme {
public:
	string name = ""; 
	int type = 0; 
	bool is_set = false;
	int value; 


	Lexeme() {
		name = "";
		type = 0;
		value = false;
	}

	Lexeme(string name) {
		this->name = name;
		type = 0;
		value = false;
	}

	Lexeme(string name, int type) {
		this->name = name;
		this->type = type;
		this->value = false;
	}

	Lexeme(string name, int type, int value) {
		this->name = name;
		this->type = type;
		this->value = value;
		this->is_set = true;
	}


	bool operator == (Lexeme b) {
		return name == b.name;
	}
};