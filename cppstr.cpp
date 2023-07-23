#include <cppstr.h>
#include <cstring>

cppstr::cppstr(const char *str) {
    this->_internal = new std::string(str);
}

cppstr::cppstr(const std::string &str) {
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
    if (beg > this->length()) {
        return;
    }
    size_t end       = beg + strlen(repl);
    *this->_internal = this->_internal->substr(0, beg) + with + this->_internal->substr(end, this->_internal->length());
}

void cppstr::replaceBetween(const char *start, const char *end, const char *with) {
    size_t start_beg = this->_internal->find(start);
    size_t start_end = start_beg + strlen(start);
    size_t end_end   = this->_internal->find(end, start_end);
    if (start_beg > this->length() || end_end > this->length()) {
        return;
    }
    *this->_internal = this->_internal->substr(0, start_end) + with +
                       this->_internal->substr(end_end, this->_internal->length());
}

size_t cppstr::length() const {
    return this->_internal->length();
}

std::string &cppstr::toString() const {
    return *this->_internal;
}

void cppstr::append(const char *str) {
    this->_internal->append(str);
}

void cppstr::append(const std::string &str) {
    this->_internal->append(str);
}

void cppstr::append(const cppstr &str) {
    this->_internal->append(*str._internal);
}

void cppstr::append(const char c) {
    this->_internal += c;
}

std::ostream &operator<<(std::ostream &s, const cppstr &cppstr) {
    return s << *cppstr._internal;
}

cppstr cppstr::operator+(const char *rhs) const {
    cppstr ret;
    ret._internal->append(*this->_internal);
    ret._internal->append(rhs);
    return ret;
}

void cppstr::operator+=(const char *rhs) {
    *this->_internal += rhs;
}

void cppstr::operator+=(char rhs) {
    *this->_internal += rhs;
}

cppstr &cppstr::operator=(const char *rhs) {
    *this->_internal = rhs;
    return *this;
}

cppstr &cppstr::operator=(const std::string &str) {
    *this->_internal = str;
    return *this;
}

bool cppstr::operator==(const std::string &rhs) const {
    return *this->_internal == rhs;
}

bool cppstr::operator==(const cppstr &rhs) const {
    return *this->_internal == *rhs._internal;
}

bool cppstr::operator==(const char *rhs) const {
    return *this->_internal == rhs;
}

cppstr::operator std::string() {
    return *this->_internal;
}

cppstr::operator std::string &() {
    return *this->_internal;
}

char &cppstr::operator[](int index) {
    if (index < 0 && index >= this->length()) {
        return this->_internal[0][this->length()];
    }
    return this->_internal[0][index];
}

char &cppstr::operator[](int index) const {
    if (index < 0 && index >= this->length()) {
        return this->_internal[0][this->length()];
    }
    return this->_internal[0][index];
}
