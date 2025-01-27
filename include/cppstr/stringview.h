#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <cstring>

namespace cppstr {

class string_view {
  public:
    string_view(char *str, size_t start, size_t end);
    char &operator[](size_t pos);
    size_t length() const;

  private:
    size_t _start;
    size_t _end;
    char *_internal;
};

} // namespace cppstr

#endif /* STRINGVIEW_H */
