#include <cppstr/cppstr.h>
#include <cstring>

namespace cppstr {

string::string(const char *str) {
    size_t length = std::strlen(str);
    this->_size   = 0;
    this->_length = length;
    if (length > 0) {
        this->_size     = length + 1;
        this->_internal = new char[this->size()];
        std::strncpy(this->_internal, str, this->_size);
        this->_internal[this->length()] = '\0';
    } else {
        this->_internal = nullptr;
    }
}

string::string() {
    this->_internal = nullptr;
    this->_size     = 0;
    this->_length   = 0;
}

string::string(const std::string &str) {
    this->_size     = str.length() + 1;
    this->_length   = str.length();
    this->_internal = new char[this->_size];
    std::strncpy(this->_internal, str.c_str(), this->_size);
    this->_internal[this->length()] = 0;
}

string::string(const string &str) {
    this->_internal = new char[str.size()];
    this->_size     = str.size();
    this->_length   = str.length();
    strncpy(this->_internal, str._internal, str.length());
    this->_internal[this->length()] = '\0';
}

string::string(string &&str) noexcept
    : _internal(std::move(str._internal)), _size(std::move(str._size)),
      _length(std::move(str._length)) {
    str._internal = nullptr;
}

string &string::operator=(string &&str) {
    this->_size     = std::move(str._size);
    this->_length   = std::move(str._length);
    this->_internal = std::move(str._internal);
    str._internal   = nullptr;
    return *this;
}

string::string(int size) {
    this->_internal = new char[size];
    this->_size     = size;
    this->_length   = 0;
}

void string::insertAfter(const string &str, const string &substr) {
    size_t ind;
    if ((ind = this->find(substr)) == string::npos) {
        return;
    }
    ind += substr.length();
    this->insert(str.c_str(), ind);
}

string::~string() {
    this->_size   = 0;
    this->_length = 0;
    delete this->_internal;
}

void string::operator=(const string &rhs) {
    if (rhs.length() == 0) {
        return;
    }
    this->resizeMaybe(rhs.length());
    this->_length = rhs.length();
    std::strncpy(this->_internal, rhs.c_str(), rhs.length());
    this->_internal[this->length()] = 0;
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
    if (this->size() < this->length() + size + 1) {
        this->_size = this->length() + size + 1;
        if (!this->_internal) {
            this->_internal = new char[this->size()];
        } else {
            this->_internal = (char *)std::realloc(this->_internal, this->size());
        }
    }
}

void string::erase() {
    this->_internal[0] = 0;
    this->_length      = 0;
}

void string::append(const char *str) {
    size_t len = std::strlen(str);
    int j      = 0;
    this->resizeMaybe(len);
    for (int i = this->length(); i < this->length() + len; i++) {
        this->_internal[i] = str[j];
        j++;
    }
    this->_length += len;
    this->_internal[this->length()] = 0;
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

string &string::operator=(const char *rhs) {
    size_t len    = std::strlen(rhs);
    this->_length = 0;
    this->resizeMaybe(len);
    this->_append(rhs, 0, len);
    this->_length        = len;
    this->_internal[len] = 0;
    return *this;
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
    tmp._length                 = i;
    tmp._internal[tmp.length()] = '\0';
    return tmp;
}

void string::operator+=(const char *rhs) {
    this->append(rhs);
}

string::operator const char *() const {
    return this->_internal;
}

char &string::operator[](int i) {
    return this->_internal[i];
}

char &string::operator[](int i) const {
    return this->_internal[i];
}

void string::insert(const char *str, int at) {
    size_t size = std::strlen(str);
    char tmp[this->length() + size];
    int end_length = this->length() + size;
    this->resizeMaybe(size);
    // copy everything from ind for later
    std::strncpy(tmp, this->_internal + at, this->length() - at);
    int i = at;
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

size_t string::find(const string &str, int offset) {
    char *p = strstr(this->_internal + offset, str._internal);
    if (p) {
        return p - this->_internal;
    }
    return string::npos;
}

// TODO: implement this lul
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

size_t string::write(const char *str, int offset) {
    if (offset > this->length()) {
        return string::npos;
    }
    size_t len     = std::strlen(str);
    int diff       = this->length() - offset;
    size_t new_len = this->length() - diff + len;
    this->resizeMaybe(new_len);
    std::strncpy(this->_internal + offset, str, len);
    if (this->length() < new_len) {
        this->_internal[new_len] = 0;
    }
    this->_length = new_len;
    return 0;
}

const char *string::c_str() const {
    return this->_internal;
}

void string::overWrite(const string &str, int offset) {
    this->resizeMaybe(str.length());
    int j = offset;
    for (int i = 0; i < str.length(); i++) {
        this->_internal[j] = str[i];
        j++;
    }
    this->_length                   = str.length() + offset;
    this->_internal[this->length()] = '\0';
}

void string::_append(const char *s, int offset, size_t s_len) {
    int diff      = this->length() - offset;
    this->_length = this->length() - diff + s_len;
    strncpy(this->_internal + offset, s, s_len);
    this->_internal[this->length()] = 0;
}

void string::_replaceGreater(const string &substr, const string &with, size_t ind) {
    size_t new_len = (with.length() - substr.length()) + this->length();
    char tmp[this->length() - ind];
    strncpy(tmp, this->c_str() + ind, this->length() - ind);
    this->resizeMaybe(with.length() - substr.length());
}

void string::replace(const string &substr, const string &with) {
    size_t ind;
    if ((ind = this->find(substr)) == string::npos) {
        return;
    }
    string tmp = this->c_str() + (ind + substr.length());
    if (with.length() > substr.length()) {
        this->resizeMaybe(with.length() - substr.length());
        this->overWrite(with, ind);
    } else {
        this->overWrite(with, ind);
    }
    this->append(tmp);
}

string_view string::getView(size_t start, size_t end) {
    string_view v(this->_internal, start, end);
    return v;
}

} // namespace cppstr
