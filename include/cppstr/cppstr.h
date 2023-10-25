#ifndef CPPSTR_H
#define CPPSTR_H

#include <iostream>
#include <string>
#include <cppstr/stringview.h>

namespace cppstr {

class string {
    friend std::ostream &operator<<(std::ostream &s, const string &cppstr);

  public:
    string(const char *str);
    string(string &str);
    string(int size = 50);
    ~string();
    string(string &&str);
    // allocated size
    size_t size() const;
    // number of chars
    size_t length() const;
    /**
     * returns index of first occurance of str
     * or cppstr::npos
     */
    size_t find(const string &str, int offset = 0);
    void append(const string &str);
    const char *c_str() const;
    // append given str starting at given index
    void appendAt(const char *str, int ind);
    // append given string after substr
    void appendAfter(const string &str, const string &substr);
    // insert given string between substring from up to substring to
    void replaceBetween(const string &str, const string &from, const string &to,
                        bool whole_match = true);
    /**
     * writes the given string into the buffer starting at ind.
     * will realloc if string doesn't fit.
     * Inserts NULL term after writing.
     */
    void overWrite(const string &str, int ind);
    string_view getView(size_t start, size_t end);
    string operator+(const char *c);
    string &operator=(string &&str);
    char &operator[](int i);
    char &operator[](int i) const;
    const static size_t npos = -1;

  private:
    char *_internal;
    // allocated size
    size_t _size;
    // number of chars
    size_t _length;
    void resizeMaybe(size_t size);
};

} // namespace cppstr

#endif /* CPPSTR_H */
