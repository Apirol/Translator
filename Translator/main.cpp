#include "Table_const.h"

int main()
{
	try
	{
		Table_const<string> table_const("filename.txt");
	}
	catch (Exception e)
	{
		cout << e.what();
	}
	return 0;
}