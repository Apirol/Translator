#include "token.h"

Token::Token() { }

Token::Token(int table_, int place_, int chain_)
{
    table = table_;
    place = place_;
    chain = chain_;
}

istream& operator >> (istream& istream_, Token &token_)
{
    istream_ >> token_.table >> token_.place >> token_.chain;
    return istream_;
}

ostream& operator << (ostream& ostream_, const Token &token_)
{
    ostream_ << token_.table << " " << token_.place << " " << token_.chain << endl;
    return ostream_;
}
