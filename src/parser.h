#include "statement.h"
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

class Parser {
public:
  Parser(Parser &&) = default;
  Parser(const Parser &) = default;
  Parser(const std::list<Token> &tk);
  Parser(std::list<Token> &&tk);
  Parser &operator=(Parser &&) = default;
  Parser &operator=(const Parser &) = default;
  ~Parser() = default;

  AbsExprPtr parse();
  void parseStmts();
  AbsStmtPtr statement();
  AbsStmtPtr printStmt();
  AbsStmtPtr exprStmt();

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

inline Parser::Parser(const std::list<Token> &tk) : tokens(tk) {
  curr = tokens.begin();
}

inline Parser::Parser(std::list<Token> &&tk) {
  tokens = std::move(tk);
  curr = tokens.begin();
}

} // namespace bello
#endif // !PARSER_H
