#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <cstring>
#include <stdexcept>

namespace cppstr {

class string_view {
  public:
    string_view(char *str, size_t start, size_t end);
    char &operator[](size_t pos);
    size_t length() const;

  private:
    size_t start;
    size_t end;
    char *str;
};

} // namespace cppstr

#endif /* STRINGVIEW_H */
