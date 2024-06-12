#include <cppstr/stringview.h>
#include <iostream>

namespace cppstr {

string_view::string_view(char *str, size_t start, size_t end) {
    this->_internal = str;
    this->_start = start;
    this->_end = end - 1;
}

size_t string_view::length() const {
    return this->_end + 2 - this->_start;
}

char &string_view::operator[](size_t pos) {
    size_t ind = pos + this->_start;
    if (ind > this->length() + this->_start) {
        std::string e = "Index " + std::to_string(pos) + " out of range of length " +
                        std::to_string(this->length());
        throw std::out_of_range(e);
    }
    return this->_internal[ind];
}

} // namespace cppstr
