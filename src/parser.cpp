#include "parser.h"
#include "errorreport.h"
#include "expr.h"
#include "lex.h"
#include "statement.h"
#include <list>
#include <memory>

using namespace bello;

SyntaxError::SyntaxError(const Token &t)
    : std::runtime_error("Error Syntax"), tk(t) {}

/*
std::vector<AbsStmtPtr> &Parser::parseStmts() {
  std::vector<AbsStmtPtr> stmts;
  for (; !isAtEnd() && peek().type != TOKEN_TYPE::EOFI;) {
    auto stmttmp = statement();
    stmts.push_back(stmttmp);
  }

  statements = stmts;
  return statements;
}

AbsStmtPtr Parser::statement() {
  if (match({TOKEN_TYPE::PRINT}))
    return printStmt();

  return exprStmt();
}

AbsStmtPtr Parser::printStmt() {
  AbsExprPtr expr = expression();
  consume(TOKEN_TYPE::SEMICOLON, "Expect ';' after value");
  return std::make_shared<PrintStmt>(expr);
}

AbsStmtPtr Parser::exprStmt() {
  AbsExprPtr expr = expression();
  consume(TOKEN_TYPE::SEMICOLON, "Expect ';' after value");
  return std::make_shared<ExprStmt>(expr);
}
*/
AbsExpr::ptr Parser::expression() { return equality(); }

AbsExpr::ptr Parser::equality() {
  AbsExpr::ptr expr = comparison();

  while (match(std::vector<TOKEN_TYPE>{TOKEN_TYPE::EQUAL_EQUAL,
                                       TOKEN_TYPE::NOT_EQUAL})) {
    Token operater = previous();
    AbsExpr::ptr right = comparison();
    expr = BinaryExpr::create(expr, right, operater);
  }

  return expr;
}

AbsExpr::ptr Parser::comparison() {
  AbsExpr::ptr expr = term();
  while (match({TOKEN_TYPE::GREATER, TOKEN_TYPE::GREATER_EQUAL,
                TOKEN_TYPE::LESS, TOKEN_TYPE::LESS_EQUAL})) {
    Token operater = previous();
    AbsExpr::ptr right = term();
    expr = BinaryExpr::create(expr, right, operater);
  }
  return expr;
}

AbsExpr::ptr Parser::term() {
  AbsExpr::ptr expr = factor();
  while (match({TOKEN_TYPE::MINUS, TOKEN_TYPE::PLUS})) {
    Token operater = previous();
    AbsExpr::ptr right = factor();
    expr = BinaryExpr::create(expr, right, operater);
  }
  return expr;
}

AbsExpr::ptr Parser::factor() {
  AbsExpr::ptr expr = unary();
  while (match({TOKEN_TYPE::STAR, TOKEN_TYPE::SLASH})) {
    Token operater = previous();
    AbsExpr::ptr right = unary();
    expr = BinaryExpr::create(expr, right, operater);
  }
  return expr;
}

AbsExpr::ptr Parser::unary() {
  AbsExpr::ptr expr;
  if (match({TOKEN_TYPE::NOT, TOKEN_TYPE::MINUS})) {
    Token operater = previous();
    AbsExpr::ptr right = unary();
    return UnaryExpr::create(right, operater);
  }
  return primary();
}

AbsExpr::ptr Parser::primary() {
  if (match({TOKEN_TYPE::FALSE}))
    return LiteralExpr::create(previous());
  if (match({TOKEN_TYPE::TRUE}))
    return LiteralExpr::create(previous());
  if (match({TOKEN_TYPE::NIL}))
    return LiteralExpr::create(previous());
  if (match({TOKEN_TYPE::NUMBER, TOKEN_TYPE::STRING, TOKEN_TYPE::IDENTIFIER}))
    return LiteralExpr::create(previous());

  if (match({TOKEN_TYPE::LEFT_PAREN})) {
    AbsExpr::ptr expr = expression();
    consume(TOKEN_TYPE::RIGHT_PAREN, "Expect ')' after expression.");
    return GroupExpr::create(expr);
  }
  // return nullptr;
}

Token &Parser::consume(TOKEN_TYPE type, bstring message) {
  if (check(type))
    return advance();
  error(peek(), message);
  return peek();
  // throw b;
}

void Parser::synchronize() {
  advance();

  while (isAtEnd()) {
    if (previous().type == TOKEN_TYPE::SEMICOLON)
      return;

    switch (peek().type) {
    case TOKEN_TYPE::FOR:
    case TOKEN_TYPE::WHILE:
    case TOKEN_TYPE::IF:
    case TOKEN_TYPE::CLASS:
    case TOKEN_TYPE::FUNC:
    case TOKEN_TYPE::PRINT:
    case TOKEN_TYPE::VAR:
      return;
    }

    advance();
  }
}

Token &Parser::previous() {
  auto prev = curr;
  prev--;
  return *prev;
}

Token &Parser::peek() { return *curr; }

bool Parser::match(std::vector<TOKEN_TYPE> types) {
  for (auto type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }

  return false;
}

bool Parser::check(TOKEN_TYPE type) {
  if (isAtEnd()) {
    return false;
  } else {
    return peek().type == type;
  }
}

Token &Parser::advance() { return *(++curr); }

bool Parser::isAtEnd() const { return curr == tokens.end(); }

void Parser::error(const Token &tk, bstring msg) {
  if (tk.type == TOKEN_TYPE::EOFI) {
    ErrorReport::reporter().error(tk, " at end" + msg);
  } else {
    ErrorReport::reporter().error(tk, msg);
  }
  throw SyntaxError(tk);
}

AbsExpr::ptr Parser::parse() {
  AbsExpr::ptr expr;
  try {
    expr = expression();
  } catch (SyntaxError &serror) {
    return expr;
  }
  return expr;
}
