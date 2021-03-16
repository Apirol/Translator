#include "Table_var.h"

bool Table_var::add_lexeme(Lexeme lexeme) {
	int ind_hash = calc_hash(lexeme.name);
	bool check = is_contains(lexeme.name);
	if (!check) {
		our_table[ind_hash].push_back(lexeme);
		return true;
	}
	else
		return false;
}

bool Table_var::set_type(std::string ind_name, int type) {
	int ind_hash = calc_hash(ind_name);
	if (is_contains(ind_name)) {
		int ind_num = find_in_vector(ind_hash, ind_name);
		our_table[ind_hash][ind_num].type = type;
		return true;
	}
	else
		return false;
}

bool Table_var::set_value(std::string ind_name, int val) {
	int ind_hash = calc_hash(ind_name);
	if (is_contains(ind_name)) {
		int ind_num = find_in_vector(ind_hash, ind_name); 
		our_table[ind_hash][ind_num].value = val;
		our_table[ind_hash][ind_num].is_set = true;
		return true;
	}
	else
		return false;
}

bool Table_var::set_type(int hash, int numb, int type) {
	if (hash >= 0 && hash < hash_N && numb >= 0 && numb < our_table[hash].size()) {
		our_table[hash][numb].type = type;
		return true;
	}
	return false;
}

bool Table_var::set_value(int hash, int numb, bool val) {
	if (hash >= 0 && hash < hash_N && numb >= 0 && numb < our_table[hash].size()) {
		our_table[hash][numb].value = val;
		our_table[hash][numb].is_set = true;
		return true;
	}
	return false;
}

bool Table_var::set_name(int hash, int numb, string name) {
	if (hash >= 0 && hash < hash_N && numb >= 0 && numb < our_table[hash].size()) {
		Lexeme update = our_table[hash][numb];
		update.name = name;
		auto i = find(our_table[hash].begin(), our_table[hash].end(), our_table[hash][numb]);
		our_table[hash].erase(i);
		add_lexeme(update);
		return true;
	}
	return false;
}

bool Table_var::is_contains(string ind_name) {
	int ind_hash = calc_hash(ind_name);

	int num = find_in_vector(ind_hash, ind_name); 

	return num != -1 ? true : false;
}

int Table_var::find_in_vector(int hash, string ind_name) {
	Lexeme find_t(ind_name);
	for (int i = 0; i < our_table[hash].size(); i++)
		if (find_t == our_table[hash][i])
			return i;
	return -1;
}

bool Table_var::get_location(string ind_name, int& hash, int& numb) {
	hash = calc_hash(ind_name);
	numb = find_in_vector(hash, ind_name);
	return numb != -1 ? true : false;
}

bool Table_var::get_lexeme(string ind_name, Lexeme& gets_Lexeme) {
	int hash, numb;
	bool check = get_location(ind_name, hash, numb);
	if (check) {
		gets_Lexeme = our_table[hash][numb];
		return true;
	}
	return false;
}

bool Table_var::get_lexeme(int hash, int numb, Lexeme& gets_Lexeme) {
	if (hash >= 0 && hash < hash_N && numb >= 0 && numb < our_table[hash].size()) {
		gets_Lexeme = our_table[hash][numb];
		return true;
	}
	else
		return false;
}



int Table_var::calc_hash(string ind_name) {
	if ('0' <= ind_name[0] && ind_name[0] <= '9')
		return ind_name[0] - '0';
	if ('a' <= ind_name[0] && ind_name[0] <= 'z')
		return ind_name[0] - 'a' + 10;
	if ('A' <= ind_name[0] && ind_name[0] <= 'Z')
		return ind_name[0] - 'A' + 36;
	return 0;
}