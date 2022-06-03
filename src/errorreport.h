#ifndef ERRORREPORT_H
#define ERRORREPORT_H

#include "lex.h"

namespace bello {

enum class MsgLevel {
  ERROR = 1,
  WARNING,
  NOTE
};


class ErrorReport {
public:
  static ErrorReport &reporter();
  void print(MsgLevel mlv, const Token &tk, bstring msg);
  void error(const Token &tk, bstring msg);
  void warning(const Token &tk, bstring msg);
  void note(const Token &tk, bstring msg);
protected:
  ErrorReport() = default;
  ErrorReport(const ErrorReport &) = default;
  ErrorReport(ErrorReport &&) = default;
  ErrorReport &operator=(const ErrorReport &) = default;
  ErrorReport &operator=(ErrorReport &&) = default;
};

} // namespace bello
#endif // ERRORREPORT_H
