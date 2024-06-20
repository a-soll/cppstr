#include <cppstr/sparam.h>

namespace cppstr {

std::ostream &operator<<(std::ostream &s, const sparam &p) {
    return s << p._internal;
}

sparam::sparam(const char *str) {
    this->_length = strlen(str);
    this->_internal = str;
}

char sparam::operator[](int i) const {
    return this->_internal[i];
}

sparam::operator const char *() const {
    return this->_internal;
}

} // namespace cppstr
