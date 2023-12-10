#ifndef CPPSTR_H
#define CPPSTR_H

#include <cppstr/stringview.h>
#include <iostream>
#include <string>

namespace cppstr {

class string {
    friend std::ostream &operator<<(std::ostream &s, const string &cppstr);

  public:
    string();
    string(const char *str);
    string(const std::string &str);
    string(const string &str);
    // init with empty string but allocated size
    string(int size);
    ~string();
    string(string &&str) noexcept;
    // allocated size
    size_t size() const;
    // number of chars
    size_t length() const;
    /**
     * clear string contents without deallocating.
     */
    void erase();
    /**
     * returns index of first occurance of str
     * or cppstr::npos.
     * optional offset to start search from.
     */
    size_t find(const string &str, int offset = 0);
    void append(const string &str);
    void append(const char *str);
    const char *c_str() const;
    // insert given str starting at given index
    void insert(const char *str, int at);
    // insert given string after substr
    void insertAfter(const string &str, const string &substr);
    // insert given string between substring from up to substring to
    void replaceBetween(const string &str, const string &from, const string &to,
                        bool whole_match = true);
    // replace substr
    void replace(const string &substr, const string &with);
    /**
     * writes the given string into the buffer starting at offset.
     * will realloc if string doesn't fit.
     * Inserts NULL term after writing.
     */
    void overWrite(const string &str, int offset);
    /**
     * writes str starting at offset.
     * does not insert null term unless str exceeds length.
     * returns string::npos if offset > length.
     */
    size_t write(const char *str, int offset = 0);
    string_view getView(size_t start, size_t end);
    string operator+(const char *c);
    string &operator=(string &&str);
    string &operator=(const char *rhs);
    void operator=(const string &rhs);
    void operator+=(const char *rhs);
    operator const char *() const;
    char &operator[](int i);
    char &operator[](int i) const;
    const static size_t npos = -1;

  private:
    char *_internal;
    // allocated size
    size_t _size;
    // number of chars
    size_t _length;
    /**
     * pass just length of string to append.
     * - if size == 0, do nothing
     * - accounts for null term.
     * - will allocate if nullptr,
     *   realloc if already allocated.
     * - reallocates to this->length + size + 1.
     * - if reallocated, this function sets the new this->_size.
     */
    void resizeMaybe(size_t size);
    // returns true if index < this->length
    bool boundsOk(int ind);
    /**
     * append s, with already calculated size len, starting from offset.
     * assumes resizeMaybe already called.
     */
    void _append(const char *s, int offset, size_t s_len);
};

} // namespace cppstr

#endif /* CPPSTR_H */
