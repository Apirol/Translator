#include "Table_const.h"
#include "Table_var.h"

int main()
{
	try
	{
		Table_const<string> operators("operators.txt");
		operators.add("&");
		operators.output("operators_out.txt");

		Table_const<string> keywords("keywords.txt");
		cout << "Is contains main: " << keywords.is_contains("main") << endl;;
		//cout << "Is contains if: " << keywords.is_contains("if");

		Table_const<string> alphabet("alphabet.txt");
		string elem = "";
		alphabet.get_val(5, elem);
		cout << "Elen with num 5: " << elem << endl;
		int num = 0;
		alphabet.get_num("c", num);
		cout << "Position number: " << num << endl;

		Table_var constants;
		Table_var variables;

		variables.add_lexeme(Lexeme("first", 0));
		variables.add_lexeme(Lexeme("second", 0));

		Lexeme lexeme;
		int hash, chain;
		constants.add_lexeme(lexeme);
		constants.set_name(0, 0, "test");
		constants.set_type("", 0);
		constants.set_value("", 10);
		constants.add_lexeme(Lexeme("third", 10, 0));

		Lexeme lexeme_get;
		variables.get_lexeme("first", lexeme_get);
		cout << lexeme_get.name << endl;

		Lexeme another_one;
		variables.get_location("second", hash, chain);
		variables.get_lexeme(hash, chain, another_one);
		cout << "Name: " << another_one.name << endl;
		cout << "Type: " << another_one.type << endl;
		

	}
	catch (Exception e)
	{
		cout << e.what();
	}
	return 0;
}