#include <cppstr.h>
#include <cstring>
#include <iostream>

cppstr::cppstr(const char *str) {
    this->_internal = new std::string(str);
}

cppstr::cppstr(std::string str) {
    this->_internal = new std::string(str);
}

cppstr::cppstr() {
    this->_internal = new std::string();
}

cppstr::~cppstr() {
    delete this->_internal;
}

void cppstr::replace(const char *repl, const char *with) {
    size_t beg = this->_internal->find(repl);
    size_t end = beg + strlen(repl);
    *this->_internal = this->_internal->substr(0, beg) + with + this->_internal->substr(end, this->_internal->length());
}

void cppstr::replaceBetween(const char *start, const char *end, const char *with) {
    size_t start_beg = this->_internal->find(start);
    size_t start_end = start_beg + strlen(start);
    size_t end_end = this->_internal->find(end, start_end);
    *this->_internal = this->_internal->substr(0, start_end) + with +
                       this->_internal->substr(end_end, this->_internal->length());
}

size_t cppstr::length() {
    return this->_internal->length();
}

std::ostream &operator<<(std::ostream &s, const cppstr &cppstr) {
    return s << *cppstr._internal;
}

cppstr cppstr::operator+(const char *rhs) {
    cppstr ret = *this;
    *ret._internal += rhs;
    return ret;
}

void cppstr::operator+=(const char *rhs) {
    *this->_internal += rhs;
}

void cppstr::operator=(const char *rhs) {
    *this->_internal = rhs;
}

void cppstr::operator=(std::string str) {
    *this->_internal = str;
}

cppstr::operator std::string() {
    return *this->_internal;
}

cppstr::operator std::string &() {
    return *this->_internal;
}
