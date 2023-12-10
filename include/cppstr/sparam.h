#ifndef SPARAM_H
#define SPARAM_H

#include <cstring>
#include <iostream>

namespace cppstr {

class sparam {
    friend std::ostream &operator<<(std::ostream &s, const sparam &p);

  public:
    sparam(const char *str);
    template <typename string> sparam(const string &str) {
        this->_len      = str->length();
        this->_internal = str->c_str();
    }
    size_t length() const;
    char operator[](int i) const;

  private:
    size_t _len;
    const char *_internal;
};

} // namespace cppstr

#endif /* SPARAM_H */
