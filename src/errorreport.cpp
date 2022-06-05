#include "errorreport.h"

const char *LevelStr[] = {"", "error", "warning", "note"};

void bello::ErrorReport::print(bello::MsgLevel mlv, const bello::Token &tk,
                               bstring msg) {
  std::printf("%s(%lu): %s: %s : %s \n", "", tk.line,
              LevelStr[static_cast<int>(mlv)], tk.literal.c_str(), msg.c_str());
}

void bello::ErrorReport::error(const bello::Token &tk, bstring msg) {
  print(MsgLevel::ERROR, tk, msg);
}

bello::ErrorReport &bello::ErrorReport::reporter() {
  static ErrorReport reporter;
  return reporter;
}

void bello::ErrorReport::warning(const bello::Token &tk, bstring msg) {
  print(MsgLevel::WARNING, tk, msg);
}

void bello::ErrorReport::note(const bello::Token &tk, bstring msg) {
  print(MsgLevel::NOTE, tk, msg);
}
