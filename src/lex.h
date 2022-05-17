#ifndef BELLO_SRC_LEX_H
#define BELLO_SRC_LEX_H
#include "types.h"

#include <cstdint>
#include <functional>
#include <istream>
#include <list>
#include <map>

namespace bello {

//void ireport(const int line, bstring where, bstring message);
//void error(const int line, bstring message);
//void error(const int line, const char* message);

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
  STAR,  // *
  SLASH, // /
  DOUBLE_SLASH,
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

static std::map<bstring, TOKEN_TYPE> KeyWords{
    {"and", TOKEN_TYPE::AND},     {"or", TOKEN_TYPE::OR},
    {"if", TOKEN_TYPE::IF},       {"else", TOKEN_TYPE::ELSE},
    {"while", TOKEN_TYPE::WHILE}, {"while", TOKEN_TYPE::WHILE}};

class Scanner {
public:
  Scanner();
  Scanner(const std::string &src);
  std::list<Token> &scanTokens();

protected:
  void scanToken(bstring &line);
  void addToken(TOKEN_TYPE type);
  bool match(bstring matchStr);
  void advance();
  void strings();
  void identifier();
  void number();

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
