#include "translator.h"

Translator::Translator()
{
    letters.read("files/table_letters.txt");
    numbers.read("files/table_numbers.txt");
    operations.read("files/table_operations.txt");
    keywords.read("files/table_keywords.txt");
    separators.read("files/table_separators.txt");
}

bool Translator::analyze_lexical(string file_source, string file_tokens, string file_error)
{
    in_source.open(file_source.c_str(), ios::in);
    out_token.open(file_tokens.c_str(), ios::out);
    out_error.open(file_error.c_str(), ios::out);
    bool flag_error = false;
    bool flag_coment = false;
    string str;
    analyze_lexical_strnum = 1;
    while (!in_source.eof() && !flag_error)
    {
        getline(in_source, str);
        if (!in_source.eof())
        {
            analyze_lexical_strinc = 0;
            string strold = str;
            if (!analyze_lexical_decomment(str, true))
            {
                out_error << "Error in string " << analyze_lexical_strnum << ": " << strold << endl;
                cout << "Error in string " << analyze_lexical_strnum << ": " << strold << endl;
                return false;
            }
            analyze_lexical_strnum += analyze_lexical_strinc;
            flag_error = !analyze_lexical_string(str);
            if (flag_error)
            {
                out_error << "Error in string " << analyze_lexical_strnum << ": " << str << endl;
                cout << "Error in string " << analyze_lexical_strnum << ": " << str << endl;
            }
            analyze_lexical_strnum++;
        }
    }
    in_source.close();
    out_token.close();
    out_error.close();
    return !flag_error;
}

bool Translator::analyze_lexical_decomment(string& str, bool is_changed)
{
    if (str.size())
    {
        bool change = false;
        size_t index_c = str.find("//"), index_c1 = str.find("/*"), index_c2;
        if (index_c != string::npos && index_c < index_c1)
        {
            str.erase(index_c);
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");
        if (index_c2 < index_c1)
        {
            out_error << "Error: incorrect coment" << endl;
            cout << "Error: incorrect coment" << endl;
            return false;
        }
        while (index_c1 != string::npos && index_c2 != string::npos)
        {
            string tmpstr = str;
            str.erase(index_c1);
            tmpstr.erase(0, index_c2 + 2);
            str += tmpstr;
            index_c1 = str.find("/*");
            index_c2 = str.find("*/");
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");
        if (index_c1 != string::npos && index_c2 == string::npos)
        {
            str.erase(index_c1);
            string tmpstr;
            if (!in_source.eof())
            {
                getline(in_source, tmpstr);
                analyze_lexical_strinc++;
            }
            else
            {
                out_error << "Error: incorrect coment" << endl;
                cout << "Error: incorrect coment" << endl;
                return false;
            }
            while (tmpstr.find("*/") == string::npos)
            {
                if (!in_source.eof())
                {
                    getline(in_source, tmpstr);
                    analyze_lexical_strinc++;
                }
                else
                {
                    out_error << "Error: incorrect coment" << endl;
                    cout << "Error: incorrect coment" << endl;
                    return false;
                }
            }
            index_c2 = tmpstr.find("*/");
            tmpstr.erase(0, index_c2 + 2);
            str += " " + tmpstr;
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");
        if (index_c1 != string::npos && index_c2 == string::npos ||
            index_c1 == string::npos && index_c2 != string::npos)
        {
            out_error << "Error: incorrect coment" << endl;
            cout << "Error: incorrect coment" << endl;
            return false;
        }
        if (is_changed)
            return analyze_lexical_decomment(str, change);
    }
    return true;
}


bool Translator::analyze_lexical_string(string str)
{
    trim(str);
    bool flag_error = false;
    if (str.size())
    {
        cout << "analyze_lexical_string started with str = " << str << endl;
        char sym_1 = str[0], sym_2 = str[1];
        // Проверка первого символа
        string str_1, str_2;
        stringstream str_stream;
        str_stream << sym_1;
        str_1 = str_stream.str();
        str_stream << sym_2;
        str_2 = str_stream.str();
        int first_sym_type = -1;
        if (letters.is_contains(sym_1))
            first_sym_type = 0;
        if (numbers.is_contains(sym_1) || sym_1 == '-')
            first_sym_type = 1;
        if (operations.is_contains(str_1) || operations.is_contains(str_2))
            first_sym_type = 2;
        if (separators.is_contains(sym_1))
            first_sym_type = 3;

        switch (first_sym_type)
        {
        case 0: // Идентификатор
        {
            string idname = str;
            int i;
            bool finded = false;
            for (i = 1; i < idname.size() && !finded; i++)
                finded = !(letters.is_contains(str[i]) || numbers.is_contains(str[i]));
            if (finded)
            {
                idname.erase(i - 1);
                str.erase(0, i - 1);
            }
            else
                str.erase(0);
            trim(idname);
            trim(str);
            if (keywords.is_contains(idname)) // Если ключевое слово
            {
                if (keywords.get_num(idname, i))
                    out_token << Token(3, i, -1);
            }
            else 
            {
                Lexeme current = Lexeme(idname);
                identifiers.add_lexeme(current);
                int table, chain;
                identifiers.get_location(idname, table, chain);
                out_token << Token(5, table, chain);
            }
            return analyze_lexical_string(str);
        }
        break;
        case 1:  // Константа
        {
            string constval = str;
            int i;
            bool finded = false;
            for (i = 1; i < constval.size() && !finded; i++)
                finded = !(numbers.is_contains(str[i]) || str[i] == '.' || str[i] == ' ');
            string str_t1, str_t2;
            stringstream str_stream_t;
            str_stream_t << str[i - 1];
            str_t1 = str_stream_t.str();
            str_stream_t << str[i];
            str_t2 = str_stream_t.str();
            if (!operations.is_contains(str_t1) && !operations.is_contains(str_t2) && !separators.is_contains(str[i - 1]))
            {
                out_error << "Error: incorrect constant" << endl;
                cout << "Error: incorrect constant" << endl;
                return false;
            }
            if (finded)
            {
                constval.erase(i - 1);
                str.erase(0, i - 1);
            }
            else
                str.erase(0);
            trim(constval);
            trim(str);
            if (constval.find_last_of('.') - constval.find_first_of('.') != 0)
            {
                out_error << "Error: incorrect constant" << endl;
                cout << "Error: incorrect constant" << endl;
                return false;
            }
            else
            {
                Lexeme current = Lexeme(constval);
                constants.add_lexeme(current);
                int table, chain;
                identifiers.get_location(constval, table, chain);
                out_token << Token(6, table, chain);
            }
            return analyze_lexical_string(str);
        }
        break;
        case 2: // Операция
        {
            int table;
            if (operations.is_contains(str_2)) // Двухсимвольная
            {
                operations.get_num(str_2, table);
                out_token << Token(4, table, -1);
                str.erase(0, 2);
                trim(str);
                return analyze_lexical_string(str);
            }
            if (operations.is_contains(str_1)) // Односимвольная
            {
                operations.get_num(str_1, table);
                out_token << Token(4, table, -1);
                str.erase(0, 1);
                trim(str);
                return analyze_lexical_string(str);
            }
        }
        break;
        case 3: // Разделитель
        {
            int table;
            separators.get_num((const char)str[0], table);
            out_token << Token(4, table, -1);
            str.erase(0, 1);
            trim(str);
            return analyze_lexical_string(str);
        }
        break;
        default: // Непонятно что
        {
            out_error << "Error: can`t determine symbol \"" << str_1 << "\"" << endl;
            cout << "Error: can`t determine symbol \"" << str_1 << "\"" << endl;
            return false;
        }
        break;
        }
    }
    return !flag_error;
}