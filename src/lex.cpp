#include "lex.h"
#include "types.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>

#if __cplusplus > 201402L
#endif

using namespace bello;

Token::Token(const std::string &litr, const bsize_t ln, TOKEN_TYPE t)
    : literal(litr), line(ln), type(t) {}

const bstring Token::toString() const { return lexeme; }

void ireport(const int line, bstring where, bstring message) {
  std::cout << "[line " << line << "] Error " << where << ":" << message
            << std::endl;
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

void Scanner::scanToken(std::string &source) {
  start = source.begin();
  if (source.empty()) {
    return;
  }
  curr = start + 1;
  line = 1;

  while (start != source.end()) {
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
        if (curr != source.end() && *curr == '/') {
          curr++;
          while (curr != source.end()) {
            if (*curr == '\n') {
              line++;
              curr++;
              break;
            }
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
      case '!':
        addToken((match("=") ? TOKEN_TYPE::NOT_EQUAL: TOKEN_TYPE::NOT));
        break;

      case '\t':
      case '\r':
      case ' ':
        advance();
        break;
      case '"':
        strings();
        break;
      case '\n':
        line++;
        advance();
        break;
      default:
        // berror(line, "Some unknow charactors...");
        return;
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

bool Scanner::match(bstring matchStr) {
  if (matchStr.empty()) {
    return false;
  }
  if (curr != source.end() && *curr == matchStr[0]) {
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
    if (isNewLine(*curr)) {
      line++;
    }
    curr++;
  }
  curr++;
  addToken(TOKEN_TYPE::STRING);
  auto &str = tokens.back().literal;
  if (str.size() == 2 && str[0] == '"' && str[1] == '"') {
    str = std::string();
  } else if (str.size() > 2 && *str.begin() == '"' && *(str.end() - 1) == '"') {
    str = str.substr(1, str.size() - 2);
  } else {
    // nothing happend
  }
}

void Scanner::identifier() {
  while (curr != source.end()) {
    if (std::isalpha(*curr) || std::isalnum(*curr) || *curr == '_') {
      curr++;
    } else if (isNewLine(*curr)) {
      line++;
      break;
    } else {
      break;
    }
  }
  TOKEN_TYPE type = TOKEN_TYPE::IDENTIFIER;
#if __cplusplus > 201402L
  std::string_view str{start, curr};
#else
  bstring str{start, curr};
#endif

  if (KeyWords.find(str) != KeyWords.end()) {
    type = KeyWords[str];
  }
  addToken(type);
  // there can be check keyword type;
}

void Scanner::number() {
  // supporting
  // 0b01001
  // 0xFFFF
  // 0o7777 ?
  if (curr == source.end()) {
    addToken(TOKEN_TYPE::NUMBER);
    return;
  }
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
