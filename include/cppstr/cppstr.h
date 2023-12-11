#ifndef CPPSTR_H
#define CPPSTR_H

#include <cppstr/sparam.h>
#include <cppstr/stringview.h>
#include <iostream>
#include <string>

namespace cppstr {

class string {
    friend std::ostream &operator<<(std::ostream &s, const string &cppstr);

  public:
    string();
    string(const char *str);
    explicit string(const std::string &str);
    explicit string(const string &str);
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
    size_t find(const sparam &str, int offset = 0);
    void append(const sparam &str);
    const char *c_str() const;
    // insert given str starting at given index
    void insert(const sparam &str, int at);
    // insert given string after substr
    void insertAfter(const sparam &str, const sparam &substr);
    // insert given string between substring from up to substring to
    void replaceBetween(const sparam &str, const sparam &from, const sparam &to,
                        bool whole_match = true);
    // replace substr
    void replace(const sparam &substr, const sparam &with);
    /**
     * writes the given string into the buffer starting at offset.
     * will realloc if string doesn't fit.
     * Inserts NULL term after writing.
     */
    void overwrite(const sparam &str, int offset);
    /**
     * writes str starting at offset.
     * does not insert null term unless str exceeds length.
     * returns string::npos if offset > length.
     */
    size_t write(const sparam &str, int offset = 0);
    string_view getView(size_t start, size_t end);
    string operator+(const sparam &c);
    string &operator=(string &&str);
    void operator=(const char *rhs);
    void operator=(const sparam &rhs);
    void operator=(const string &rhs);
    void operator+=(const sparam &rhs);
    explicit operator const char *() const;
    operator sparam();
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
    void _append(const sparam &s, int offset);
    /**
     * overwrite without calling resize
     */
    void _overwrite(const sparam &s, int offset);
};

} // namespace cppstr

#endif /* CPPSTR_H */
