#include "lex.h"
#include "types.h"

#include <cctype>
#include <iostream>
#include <sstream>

using namespace bello;


Token::Token(const std::string &litr, const bsize_t ln, TOKEN_TYPE t)
    : literal(litr), line(ln), type(t) {}

const bstring Token::toString() const { return lexeme; }

void ireport(const int line, bstring where, bstring message) {
  std::cout << "[line " << line << "] Error " << where << ":" << message
            << std::endl;
}
void berror(const int line, bstring message) {
  ireport(line, bstring(""), bstring(message));
}

void berror(const int line, const char *message) {
  ireport(line, bstring(""), message);
}

Scanner::Scanner() : errorFlag(false) {}

Scanner::Scanner(const bstring &src) : source(src), errorFlag(false) {}

std::list<Token> &Scanner::scanTokens() {
  scanToken(source);
  return tokens;
}

void Scanner::scanToken(std::string &line) {
  start = line.begin();
  if (line.empty()) {
    return;
  }
  curr = start + 1;

  while (start != line.end()) {
    if (std::isalpha(*start)) {
      identifier();
      continue;
    } else if (std::isalnum(*start)) {
      number();
      continue;
    } else {
      switch (*start) {
      case '[':
        addToken(TOKEN_TYPE::LEFT_BRACKET);
        break;
      case ']':
        addToken(TOKEN_TYPE::RIGHT_BRACKET);
        break;
      case '(':
        addToken(TOKEN_TYPE::LEFT_PAREN);
        break;
      case ')':
        addToken(TOKEN_TYPE::RIGHT_PAREN);
        break;
      case '{':
        addToken(TOKEN_TYPE::LEFT_BRACE);
        break;
      case '}':
        addToken(TOKEN_TYPE::RIGHT_BRACE);
        break;
      case '+':
        addToken(TOKEN_TYPE::PLUS);
        break;
      case '-':
        addToken(TOKEN_TYPE::MINUS);
        break;
      case '*':
        addToken(TOKEN_TYPE::STAR);
        break;
      case '/':
        if (curr != line.end() && *curr == '/') {
          curr++;
          while (*curr != '\n' && curr != line.end()) {
            curr++;
          }
        } else {
          addToken(TOKEN_TYPE::SLASH);
        }
        break;
      case '=':
        addToken((match("=") ? TOKEN_TYPE::EQUAL_EQUAL : TOKEN_TYPE::EQUAL));
        break;
      case '>':
        addToken(
            (match("=") ? TOKEN_TYPE::GREATER_EQUAL : TOKEN_TYPE::LESS_EQUAL));
        break;
      case '<':
        addToken((match("=") ? TOKEN_TYPE::LESS_EQUAL : TOKEN_TYPE::LESS));
        break;
      case ';':
        addToken(TOKEN_TYPE::SEMICOLON);
        break;

      case '\t':
      case '\r':
      case ' ':
        advance();
        break;
      case '"':
        strings();
        break;
      default:
        // berror(line, bstring("Some unknow charactors..."));
        break;
      }
      continue;
    }
  }
  addToken(TOKEN_TYPE::EOFI);
}

void Scanner::addToken(TOKEN_TYPE type) {
  bstring literal = bstring(start, curr);
  tokens.emplace_back(literal, line, type);
  advance();
}

//
//

bool Scanner::match(bstring charactor) {

  if (curr != source.end() && *curr == charactor[0]) {
    curr++;
    return true;
  } else {
    return false;
  }
}

void Scanner::advance() {
  start = curr;
  if (curr != source.end()) {
    curr++;
  }
}

void Scanner::strings() {
  while (curr != source.end() && *curr != '"') {
    curr++;
  }
  curr++;
  addToken(TOKEN_TYPE::STRING);
}

void Scanner::identifier() {

  while (curr != source.end()) {
    if (std::isalpha(*curr) || std::isalnum(*curr) || *curr == '_') {
      curr++;
    } else {
      break;
    }
  }
  addToken(TOKEN_TYPE::IDENTIFIER);
}

void Scanner::number() {
  // supporting
  // 0b01001
  // 0xFFFF
  // 0o7777 ?
  while (curr != source.end()) {
    if (std::isalnum(*curr) || *curr == '.') {
      curr++;
    } else if (*curr == '\n') {
      addToken(TOKEN_TYPE::NUMBER);
      line++;
      break;
    } else {
      addToken(TOKEN_TYPE::NUMBER);
      break;
    }
  }
}
