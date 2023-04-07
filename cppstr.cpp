#include <cppstr.h>
#include <iostream>

CppStr::CppStr(std::string str) {
    this->str = str;
}

void CppStr::replace(std::string repl, std::string with) {
    size_t beg = this->str.find(repl);
    size_t end = beg + repl.length();
    this->str = this->str.substr(0, beg) + with + this->str.substr(end, this->str.length());
}

void CppStr::replaceBetween(std::string start, std::string end, std::string with) {
    size_t start_beg = this->str.find(start);
    size_t start_end = start_beg + start.length();
    size_t end_end = this->str.find(end, start_end);
    this->str = this->str.substr(0, start_end) + with + this->str.substr(end_end, this->str.length());
}

std::ostream& operator<<(std::ostream &s, const CppStr &cppstr) {
    return s << cppstr.str;
}
