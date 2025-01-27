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
    // constructor for std::string or cppstr::string
    template <typename T> sparam(const T *t) {
        this->_length   = t->length();
        this->_internal = t->c_str();
    }
    inline size_t length() const {
        return this->_length;
    }
    char operator[](int i) const;
    operator const char *() const;

  private:
    size_t _length;
    const char *_internal;
};

} // namespace cppstr

#endif /* SPARAM_H */
