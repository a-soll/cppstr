#include <cppstr.h>
#include <cstring>

cppstr::cppstr(const char *str) {
    size_t size     = std::strlen(str);
    this->_internal = (char *)malloc(sizeof(char) * size);
    std::strncpy(this->_internal, str, size);
    this->_size                     = size;
    this->_length                   = size;
    this->_internal[this->length()] = '\0';
}

cppstr::cppstr(cppstr &str) {
    this->_internal = (char *)malloc(str.size());
    this->_size     = str.size();
    this->_length   = str.length();
    strncpy(this->_internal, str._internal, str.length());
    this->_internal[this->length()] = '\0';
}

cppstr::cppstr(cppstr &&str) {
    *this = std::move(str);
}

cppstr &cppstr::operator=(cppstr &&str) {
    this->_size     = std::move(str._size);
    this->_length   = std::move(str._length);
    this->_internal = std::move(str._internal);
    return *this;
}

cppstr::cppstr(int size) {
    this->_internal = (char *)malloc(sizeof(char) * size);
}

cppstr::~cppstr() {
    free(this->_internal);
}

std::ostream &operator<<(std::ostream &s, const cppstr &cppstr) {
    return s << cppstr._internal;
}

size_t cppstr::size() const {
    return this->_size;
}

size_t cppstr::length() const {
    return this->_length;
}

void cppstr::resizeMaybe(size_t size) {
    if (this->size() <= this->length() + size) {
        this->_size     = this->length() + size;
        this->_internal = (char *)std::realloc(this->_internal, this->size());
    }
}

void cppstr::append(const cppstr &str) {
    this->resizeMaybe(str.length());
    int j = 0;
    for (int i = this->length(); i < this->length() + str.length(); i++) {
        this->_internal[i] = str[j];
        j++;
    }
    this->_length += str.length();
    this->_internal[this->length()] = '\0';
}

cppstr cppstr::operator+(const char *c) {
    size_t size = std::strlen(c);
    cppstr tmp(*this);
    tmp.resizeMaybe(size);
    int j = 0;
    int i = tmp.length();
    for (; i < tmp.length() + size; i++) {
        tmp._internal[i] = c[j];
        j++;
    }
    tmp._length                 = i;
    tmp._internal[tmp.length()] = '\0';
    return tmp;
}

char &cppstr::operator[](int i) {
    return this->_internal[i];
}

char &cppstr::operator[](int i) const {
    return this->_internal[i];
}

void cppstr::appendAt(const char *str, int ind) {
    size_t size = std::strlen(str);
    char tmp[this->length() + size];
    int end_length = this->length() + size;
    this->resizeMaybe(size);
    // copy everything from ind for later
    std::strncpy(tmp, this->_internal + ind, this->length() - ind);
    int i = ind;
    for (int j = 0; j < size; j++) {
        this->_internal[i] = str[j];
        i++;
    }
    int j = 0;
    // append rest of original string
    for (; i < end_length; i++) {
        this->_internal[i] = tmp[j];
        j++;
    }
    this->_length                   = end_length;
    this->_internal[this->length()] = '\0';
}

size_t cppstr::find(const cppstr &str, int offset) {
    char *p = strstr(this->_internal + offset, str._internal);
    if (p) {
        return p - this->_internal;
    }
    return cppstr::npos;
}

static bool isWholeMatch(const cppstr &str) {
    return true;
}

void cppstr::replaceBetween(const cppstr &str, const cppstr &from, const cppstr &to,
                            bool whole_match) {
    size_t from_ind;
    size_t to_ind;
    if ((from_ind = this->find(from)) == cppstr::npos) {
        return;
    }
    if ((to_ind = this->find(to, from_ind + from.length())) == cppstr::npos) {
        return;
    }
    cppstr tmp(this->c_str() + to_ind);
    this->overWrite(str, from_ind + from.length());
    this->append(tmp);
}

const char *cppstr::c_str() const {
    return this->_internal;
}

void cppstr::overWrite(const cppstr &str, int ind) {
    this->resizeMaybe(str.length());
    int j = ind;
    for (int i = 0; i < str.length(); i++) {
        this->_internal[j] = str[i];
        j++;
    }
    this->_length                   = str.length() + ind;
    this->_internal[this->length()] = '\0';
}
