#include "lex.h"
#include "types.h"

#include <iostream>
#include <sstream>

using namespace bello;

Token::Token(const std::string &litr, const bsize_t ln, TOKEN_TYPE t)
    : literal(litr), line(ln), type(t) {}

const bstring Token::toString() const { return lexeme; }

void ireport(const int line, bstring where, const bstring message) {
  std::cout << "[line " << line << "] Error " << where << ":" << message
            << std::endl;
}
void error(const int line, const bstring message) {
  ireport(line, "", message);
}

Scanner::Scanner() : errorFlag(false) {}

Scanner::Scanner(const std::string &src) : source(src), errorFlag(false) {}

std::list<Token> &Scanner::scanTokens() {
  std::istringstream ins(source);
  bstring linestr;
  while (std::getline(ins, linestr)) {
    scanToken(linestr);
    line++;
  }
}

void Scanner::scanToken(const std::string &line) {
  bstring::const_iterator start = line.cbegin();
  bstring::const_iterator curr = start;

  while (start != line.cend()) {
    switch (*start) {
    case '[':
      addToken(bstring(start, start + 1), TOKEN_TYPE::LEFT_BRACKET);
      break;
    case ']':
      addToken(bstring(start, start + 1), TOKEN_TYPE::RIGHT_BRACKET);
      break;
    case '(':
      addToken(bstring(start, start + 1), TOKEN_TYPE::LEFT_PAREN);
      break;
    case ')':
      addToken(bstring(start, start + 1), TOKEN_TYPE::RIGHT_PAREN);
      break;
    case '{':
      addToken(bstring(start, start + 1), TOKEN_TYPE::LEFT_BRACE);
      break;
    case '}':
      addToken(bstring(start, start + 1), TOKEN_TYPE::RIGHT_BRACE);
      break;
    case '+':
      addToken(bstring(start, start + 1), TOKEN_TYPE::PLUS);
      break;
    case '-':
      addToken(bstring(start, start + 1), TOKEN_TYPE::MINUS);
      break;
    case '*':
      addToken(bstring(start, start + 1), TOKEN_TYPE::STAR);
      break;
    case '/':
      addToken(bstring(start, start + 1), TOKEN_TYPE::STAR);
      break;
    }
  }
  addToken(bstring(), TOKEN_TYPE::EOFI);
}

void Scanner::addToken(bstring literal, TOKEN_TYPE type) {
  tokens.push_back(Token(literal, line, type));
}

void Scanner::match(bstring::const_iterator &start, bstring::const_iterator &curr)
{
    std::string
}

