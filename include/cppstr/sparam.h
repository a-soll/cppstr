#ifndef SPARAM_H
#define SPARAM_H

#include <cstring>
#include <iostream>

namespace cppstr {

/**
 * used as param to allow passing either `const char*` or `string`.
 * avoids needing to malloc and redundant strlen().
 */
class sparam {
    friend std::ostream &operator<<(std::ostream &s, const sparam &p);

  public:
    sparam(const char *str);
    template <typename T> sparam(const T *t) {
        this->_len      = t->length();
        this->_internal = t->c_str();
    }
    size_t length() const;
    char operator[](int i) const;
    operator const char *() const;

  private:
    size_t _len;
    const char *_internal;
};

} // namespace cppstr

#endif /* SPARAM_H */
