#ifndef PARSER_H
#include "lex.h"
#include <exception>
#include <list>
#include <vector>

#include "expr.h"

namespace bello {

class SyntaxError : public std::runtime_error {
public:
  SyntaxError(const Token &t);
  SyntaxError(SyntaxError &&) = default;
  SyntaxError(const SyntaxError &) = default;

private:
  const Token &tk;
};

class Parser : public AbsVisitor {
public:
  Parser(const std::list<Token> &tk);
  Parser(const std::list<Token> &&tk);
  Parser(Parser &&) = default;
  Parser(const Parser &) = default;
  Parser &operator=(Parser &&) = default;
  Parser &operator=(const Parser &) = default;
  ~Parser() = default;

  AbsExprPtr parse();

  AbsExprPtr expression();
  AbsExprPtr equality();
  AbsExprPtr comparison();
  AbsExprPtr term();
  AbsExprPtr factor();
  AbsExprPtr unary();
  AbsExprPtr primary();

  Token &consume(TOKEN_TYPE type, bstring message);
  void error(const Token &tk, bstring msg);
  void synchronize();

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
