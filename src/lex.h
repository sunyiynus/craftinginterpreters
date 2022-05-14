#ifndef BELLO_SRC_LEX_H
#define BELLO_SRC_LEX_H
#include "types.h"


enum class TOKEN_TYPE {
    OPERATOR,
    OPERAND
};


// special token
namespace SToken {
    const bstring DOT = ".";
    const bstring SPACE = " ";
    const bstring PLUS = "+";
    const bstring ASSIGN = "=";
    const bstring MINUS = "-";
    const bstring MULTI = "*";
}

struct Token
{
    bstring literal;
    bsize_t line;
    TOKEN_TYPE type;
};


class Lex
{
    public:
    Token advance();
private:
};


#endif // BELLO_SRC_LEX_H