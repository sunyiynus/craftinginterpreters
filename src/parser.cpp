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

std::vector<AbsStmtPtr> &Parser::parseStmts() {
  std::vector<AbsStmtPtr> stmts;
  for (; !isAtEnd();) {
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

AbsExprPtr Parser::expression() { return equality(); }

AbsExprPtr Parser::equality() {
  AbsExprPtr expr = comparison();

  while (match(std::vector<TOKEN_TYPE>{TOKEN_TYPE::EQUAL_EQUAL,
                                       TOKEN_TYPE::NOT_EQUAL})) {
    Token operater = previous();
    AbsExprPtr right = comparison();
    expr = std::make_shared<Expr<BinaryPackage>>(
        BinaryPackage(operater, expr, right));
  }

  return expr;
}

AbsExprPtr Parser::comparison() {
  AbsExprPtr expr = term();
  while (match({TOKEN_TYPE::GREATER, TOKEN_TYPE::GREATER_EQUAL,
                TOKEN_TYPE::LESS, TOKEN_TYPE::LESS_EQUAL})) {
    Token operater = previous();
    AbsExprPtr right = term();
    expr = std::make_shared<Expr<BinaryPackage>>(
        BinaryPackage(operater, expr, right));
  }
  return expr;
}

AbsExprPtr Parser::term() {
  AbsExprPtr expr = factor();
  while (match({TOKEN_TYPE::MINUS, TOKEN_TYPE::PLUS})) {
    Token operater = previous();
    AbsExprPtr right = factor();
    expr = std::make_shared<Expr<BinaryPackage>>(
        BinaryPackage(operater, expr, right));
  }
  return expr;
}

AbsExprPtr Parser::factor() {
  AbsExprPtr expr = unary();
  while (match({TOKEN_TYPE::STAR, TOKEN_TYPE::SLASH})) {
    Token operater = previous();
    AbsExprPtr right = unary();
    expr = std::make_shared<Expr<BinaryPackage>>(
        BinaryPackage(operater, expr, right));
  }
  return expr;
}

AbsExprPtr Parser::unary() {
  AbsExprPtr expr;
  if (match({TOKEN_TYPE::NOT, TOKEN_TYPE::MINUS})) {
    Token operater = previous();
    AbsExprPtr right = unary();
    return std::make_shared<Expr<UnaryPackage>>(UnaryPackage(operater, right));
  }
  return primary();
}

AbsExprPtr Parser::primary() {
  if (match({TOKEN_TYPE::FALSE}))
    return std::make_shared<Expr<LiteralPackage>>(LiteralPackage(previous()));
  if (match({TOKEN_TYPE::TRUE}))
    return std::make_shared<Expr<LiteralPackage>>(LiteralPackage(previous()));
  if (match({TOKEN_TYPE::NIL}))
    return std::make_shared<Expr<LiteralPackage>>(LiteralPackage(previous()));
  if (match({TOKEN_TYPE::NUMBER, TOKEN_TYPE::STRING, TOKEN_TYPE::IDENTIFIER}))
    return std::make_shared<Expr<LiteralPackage>>(LiteralPackage(previous()));

  if (match({TOKEN_TYPE::LEFT_PAREN})) {
    AbsExprPtr expr = expression();
    consume(TOKEN_TYPE::RIGHT_PAREN, "Expect ')' after expression.");
    return std::make_shared<Expr<GroupPackage>>(GroupPackage(expr));
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

AbsExprPtr Parser::parse() {
  AbsExprPtr expr;
  try {
    expr = expression();
  } catch (SyntaxError &serror) {
    return expr;
  }
  return expr;
}
