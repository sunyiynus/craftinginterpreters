#ifndef PARSER_H
#include "lex.h"
#include <list>
#include <vector>

#include "expr.h"

namespace bello {

class Parser : public AbsVisitor {
public:
  Parser(const std::list<Token> &tk);
  Parser(const std::list<Token> &&tk);
  Parser(Parser &&) = default;
  Parser(const Parser &) = default;
  Parser &operator=(Parser &&) = default;
  Parser &operator=(const Parser &) = default;
  ~Parser() = default;

  AbsExprPtr expression();
  AbsExprPtr equality();
  AbsExprPtr comparison();
  AbsExprPtr term();
  AbsExprPtr factor();
  AbsExprPtr unary();
  AbsExprPtr primary();

  Token &consume(TOKEN_TYPE type, bstring message);

  Token &previous();
  Token &peek();
  bool match(std::vector<TOKEN_TYPE> types);
  bool check(TOKEN_TYPE type);

  Token &advance();
  bool isAtEnd() const;

private:
  Parser() = default;
  std::list<Token> tokens;
  std::list<Token>::iterator curr;
};

} // namespace bello
#endif // !PARSER_H
