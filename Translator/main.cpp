#include "translator.h"

using namespace std;

int main()
{
    Translator a;
    cout << a.analyze_lexical("files/source.txt", "files/tokens.txt", "files/errors.txt");
    return 0;
}
