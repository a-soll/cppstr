#include <cstring>
#include <cppstr/cppstr.h>

namespace cppstr {

string::string(const char *str) {
    std::cout << str << std::endl;
    size_t size = std::strlen(str);
    this->_internal = (char *)malloc(sizeof(char) * size);
    std::strncpy(this->_internal, str, size);
    this->_size = size;
    this->_length = size;
    this->_internal[this->length()] = '\0';
}

string::string(string &str) {
    this->_internal = (char *)malloc(str.size());
    this->_size = str.size();
    this->_length = str.length();
    strncpy(this->_internal, str._internal, str.length());
    this->_internal[this->length()] = '\0';
}

string::string(string &&str) {
    *this = std::move(str);
}

string &string::operator=(string &&str) {
    this->_size = std::move(str._size);
    this->_length = std::move(str._length);
    this->_internal = std::move(str._internal);
    return *this;
}

string::string(int size) {
    this->_internal = (char *)malloc(sizeof(char) * size);
}

void string::appendAfter(const string &str, const string &substr) {
    size_t ind;
    if ((ind = this->find(substr)) == string::npos) {
        return;
    }
    ind += substr.length();
    this->appendAt(str.c_str(), ind);
}

string::~string() {
    free(this->_internal);
}

std::ostream &operator<<(std::ostream &s, const string &cppstr) {
    return s << cppstr._internal;
}

size_t string::size() const {
    return this->_size;
}

size_t string::length() const {
    return this->_length;
}

void string::resizeMaybe(size_t size) {
    if (this->size() <= this->length() + size) {
        this->_size = this->length() + size;
        this->_internal = (char *)std::realloc(this->_internal, this->size());
    }
}

void string::append(const string &str) {
    this->resizeMaybe(str.length());
    int j = 0;
    for (int i = this->length(); i < this->length() + str.length(); i++) {
        this->_internal[i] = str[j];
        j++;
    }
    this->_length += str.length();
    this->_internal[this->length()] = '\0';
}

string string::operator+(const char *c) {
    size_t size = std::strlen(c);
    string tmp(*this);
    tmp.resizeMaybe(size);
    int j = 0;
    int i = tmp.length();
    for (; i < tmp.length() + size; i++) {
        tmp._internal[i] = c[j];
        j++;
    }
    tmp._length = i;
    tmp._internal[tmp.length()] = '\0';
    return tmp;
}

char &string::operator[](int i) {
    return this->_internal[i];
}

char &string::operator[](int i) const {
    return this->_internal[i];
}

void string::appendAt(const char *str, int ind) {
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
    this->_length = end_length;
    this->_internal[this->length()] = '\0';
}

size_t string::find(const string &str, int offset) {
    char *p = strstr(this->_internal + offset, str._internal);
    if (p) {
        return p - this->_internal;
    }
    return string::npos;
}

static bool isWholeMatch(const string &str) {
    return true;
}

void string::replaceBetween(const string &str, const string &from, const string &to,
                            bool whole_match) {
    size_t from_ind;
    size_t to_ind;
    if ((from_ind = this->find(from)) == string::npos) {
        return;
    }
    if ((to_ind = this->find(to, from_ind + from.length())) == string::npos) {
        return;
    }
    string tmp(this->c_str() + to_ind);
    this->overWrite(str, from_ind + from.length());
    this->append(tmp);
}

const char *string::c_str() const {
    return this->_internal;
}

void string::overWrite(const string &str, int ind) {
    this->resizeMaybe(str.length());
    int j = ind;
    for (int i = 0; i < str.length(); i++) {
        this->_internal[j] = str[i];
        j++;
    }
    this->_length = str.length() + ind;
    this->_internal[this->length()] = '\0';
}

} // namespace cppstr
