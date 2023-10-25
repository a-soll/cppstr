#include <cppstr/stringview.h>
#include <iostream>

namespace cppstr {

string_view::string_view(char *str, size_t start, size_t end) {
    this->str = str;
    this->start = start;
    this->end = end - 1;
}

size_t string_view::length() const {
    return this->end + 1 - this->start;
}

char &string_view::operator[](size_t pos) {
    size_t ind = pos + this->start;
    if (ind > this->length() + this->start) {
        throw std::out_of_range("Index out of range");
    }
    return this->str[ind];
}

} // namespace cppstr
