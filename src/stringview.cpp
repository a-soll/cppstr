#include <cppstr/stringview.h>
#include <iostream>

namespace cppstr {

string_view::string_view(char *str, size_t start, size_t end) {
    this->str = str;
    this->start = start;
    this->end = end - 1;
}

size_t string_view::length() const {
    return this->end + 2 - this->start;
}

char &string_view::operator[](size_t pos) {
    size_t ind = pos + this->start;
    if (ind > this->length() + this->start) {
        std::string e = "Index " + std::to_string(pos) + " out of range of length " + std::to_string(this->length());
        throw std::out_of_range(e);
    }
    return this->str[ind];
}

} // namespace cppstr
