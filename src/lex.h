#ifndef BELLO_SRC_LEX_H
#define BELLO_SRC_LEX_H
#include "types.h"

#include <cstdint>
#include <functional>
#include <istream>
#include <list>

namespace bello {

void ireport(const int line, bstring where, const bstring message);
void error(const int line, const bstring message);

enum class TOKEN_TYPE {
  // single charactor token
  LEFT_BRACKET,
  RIGHT_BRACKET, // []
  LEFT_PAREN,
  RIGHT_PAREN, // ()
  LEFT_BRACE,
  RIGHT_BRACE, // {}
  SEMICOLON,
  COMMA,
  DOT,
  PLUS,
  MINUS,
  STAR,         // *
  SLASH,        // /
  PERCENT_SIGN, // %
  // one or two charactor
  NOT_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  // literal
  IDENTIFIER,
  STRING,
  NUMBER,
  // keywords
  CLASS,
  FUNC,
  IF,
  ELSE,
  FOR,
  RETURN,
  NIL,
  OR,
  AND,
  NOT,
  PRINT,
  THIS,
  TRUE,
  FALSE,
  VAR,
  WHILE,
  EOFI
};

// special token
namespace SToken {
const bstring DOT = ".";
const bstring SPACE = " ";
const bstring PLUS = "+";
const bstring ASSIGN = "=";
const bstring MINUS = "-";
const bstring MULTI = "*";
} // namespace SToken

struct Token {
  Token(const std::string &litr, bsize_t line, TOKEN_TYPE t);
  bstring literal;
  bstring lexeme;
  bsize_t line;
  TOKEN_TYPE type;
  const bstring toString() const;
};

class Scanner {
public:
  Scanner();
  Scanner(const std::string &src);
  std::list<Token> &scanTokens();
  void scanToken(const bstring &line);
  void addToken(bstring literal, TOKEN_TYPE type);
    void match(bstring::const_iterator& start, bstring::const_iterator& curr);

private:
  bool errorFlag;
  bstring source;

  std::list<Token> tokens;

  // control tokenize
  int line;
  bstring::iterator start;
  bstring::iterator curr;
};

} // namespace bello

#endif // BELLO_SRC_LEX_H
