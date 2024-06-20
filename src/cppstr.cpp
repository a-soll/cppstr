#include <chrono>
#include <cppstr/cppstr.h>
#include <cstring>

namespace cppstr {

using namespace std::chrono;

string::string(const char *str) {
    this->_length = std::strlen(str);
    this->_size = this->_length;

    if (this->_length > string::_sso_size) {
        this->_internal = new char[this->_length + 1];
    } else {
        this->_internal = this->_sso;
    }
    std::memcpy(this->_internal, str, this->_length);
    this->_internal[this->_length] = '\0';
}

string::string() {
    this->_size = 0;
    this->_length = 0;
    this->_internal = nullptr;
}

string::string(const std::string &str) {
    this->_size = str.capacity();
    this->_length = str.length();
    this->_internal = new char[this->_size];
    std::memcpy(this->_internal, str.c_str(), this->_size);
    this->_internal[this->_length] = 0;
}

string::string(const string &str) {
    this->_size = str._size;
    this->_length = str._length;
    if (str._length > string::_sso_size) {
        this->_internal = new char[this->_size];
        std::memcpy(this->_internal, str._internal, str._length);
        this->_internal[this->_length] = 0;
    } else {
        std::memcpy(this->_sso, str._sso, str._length);
        this->_sso[this->_length] = 0;
        this->_internal = this->_sso;
    }
}

string::string(string &&str) noexcept
    : _internal(std::move(str._internal)), _size(std::move(str._size)),
      _length(std::move(str._length)) {
    str._internal = nullptr;
}

string &string::operator=(string &&str) {
    this->_size = std::move(str._size);
    this->_length = std::move(str._length);
    this->_internal = std::move(str._internal);
    str._internal = nullptr;
    return *this;
}

string::string(size_t size) {
    this->_internal = new char[size];
    this->_size = size;
    this->_length = 0;
}

void string::insertAfter(const sparam &str, const sparam &substr) {
    size_t ind;
    if ((ind = this->find(substr)) == string::npos) {
        return;
    }
    ind += substr.length();
    this->insert(str, ind);
}

string::~string() {
    if (this->_internal != this->_sso) {
        delete this->_internal;
    }
}

void string::operator=(const char *rhs) {
    *this = sparam(rhs);
}

void string::operator=(const string &rhs) {
    if (rhs.length() == 0) {
        return;
    }
    if (this->size() < rhs._size) {
        this->_resizeMaybe(rhs._size);
    }
    this->_length = rhs.length();
    std::memcpy(this->_internal, rhs.c_str(), rhs._length);
    this->_internal[this->_length] = 0;
}

std::ostream &operator<<(std::ostream &s, const string &cppstr) {
    return s << cppstr.c_str();
}

size_t string::size() const {
    return this->_size;
}

size_t string::length() const {
    return this->_length;
}

void string::_resize(size_t size) {
    if (!this->_internal) {
        this->_internal = new char[size];
    } else {
        this->_internal = (char *)std::realloc(this->_internal, size);
    }
    this->_size = size;
}

void string::_resizeMaybe(size_t size) {
    bool resize = false;
    while (this->_size < this->_length + size + 1) {
        if (this->_size == 0) {
            this->_size = this->_length + size + 1;
        } else {
            this->_size *= 2;
        }
        resize = true;
    }
    if (resize) {
        char *tmp = new char[this->_size];
        std::memcpy(tmp, this->_internal, this->_length);
        tmp[this->_length] = 0;
        if (this->_internal != this->_sso) {
            delete this->_internal;
        }
        this->_internal = tmp;
    }
}

void string::erase() {
    this->_internal[0] = 0;
    this->_length = 0;
}

void string::append(const sparam &str) {
    size_t str_len = str.length();
    this->_resizeMaybe(str_len);
    std::memcpy(this->_internal + this->_length, str, str_len);
    this->_length += str_len;
    this->_internal[this->_length] = 0;
}

void string::operator=(const sparam &rhs) {
    size_t len = rhs.length();
    this->_length = 0;
    this->_resizeMaybe(len);
    this->_append(rhs, 0);
    this->_length = len;
    this->_internal[len] = 0;
}

string string::operator+(const sparam &c) const {
    size_t size = c.length();
    string tmp(*this);
    tmp._resizeMaybe(size);
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

void string::operator+=(const sparam &rhs) {
    this->append(rhs);
}

bool string::operator==(const sparam &rhs) const {
    return strcmp(this->_internal, rhs) == 0;
}

char &string::operator[](int i) {
    return this->_internal[i];
}

char string::operator[](int i) const {
    return this->_internal[i];
}

void string::insert(const sparam &str, int at) {
    if (at == string::npos) {
        return;
    }
    size_t size = str.length();
    char tmp[this->_length + size];
    int end_length = this->_length + size;
    this->_resizeMaybe(size);
    // copy everything from ind for later
    std::memcpy(tmp, this->_internal + at, this->_length - at);
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
    this->_length = end_length;
    this->_internal[this->_length] = '\0';
}

size_t string::find(const sparam &str, int offset) const {
    char *p = strstr(this->_internal + offset, str);
    if (p) {
        return p - this->_internal;
    }
    return string::npos;
}

// TODO: implement this lul
static bool isWholeMatch(const string &str) {
    return true;
}

void string::chop(int ind) {
    if (ind > this->_length) {
        return;
    }
    this->_internal[ind] = 0;
    this->_length = ind - 1;
}

void string::replaceBetween(const sparam &str, const sparam &from, const sparam &to,
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
    this->overwrite(str, from_ind + from.length());
    this->append(tmp);
}

size_t string::write(const sparam &str, int offset) {
    if (offset > this->_length) {
        return string::npos;
    }
    int diff = this->_length - offset;
    size_t new_len = this->_length - diff + str.length();
    this->_resizeMaybe(new_len);
    std::memcpy(this->_internal + offset, str, str.length());
    if (this->_length < new_len) {
        this->_internal[new_len] = 0;
    }
    this->_length = new_len;
    return 0;
}

void string::overwrite(const sparam &str, int offset) {
    this->_resizeMaybe(str.length());
    this->_overwrite(str, offset);
}

void string::_overwrite(const sparam &s, int offset) {
    int j = offset;
    for (int i = 0; i < s.length(); i++) {
        this->_internal[j] = s[i];
        j++;
    }
    this->_length = s.length() + offset;
    this->_internal[this->_length] = '\0';
}

void string::_append(const sparam &s, int offset) {
    int diff = this->_length - offset;
    this->_length = this->_length - diff + s.length();
    std::memcpy(this->_internal + offset, s, s.length());
    this->_internal[this->_length] = 0;
}

void string::replace(const sparam &substr, const sparam &with) {
    size_t ind;
    if ((ind = this->find(substr)) == string::npos) {
        return;
    }
    size_t tmp_len = this->_length - (ind + substr.length());
    char tmp[tmp_len];
    std::memcpy(tmp, this->c_str() + (ind + substr.length()), tmp_len);
    tmp[tmp_len] = 0;
    if (with.length() > substr.length()) {
        this->_resizeMaybe(with.length() - substr.length());
    }
    this->_overwrite(with, ind);
    this->append(tmp);
}

string_view string::getView(size_t start, size_t end) {
    string_view v(this->_internal, start, end);
    return v;
}

string::operator sparam() {
    return this;
}

} // namespace cppstr
