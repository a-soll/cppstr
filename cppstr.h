#ifndef CPPSTR_H
#define CPPSTR_H

#include <iostream>
#include <string>

class cppstr {
    friend std::ostream &operator<<(std::ostream &s, const cppstr &cppstr);

  public:
    cppstr(const char *str);
    cppstr(cppstr &str);
    cppstr(int size = 50);
    cppstr();
    ~cppstr();
    cppstr(cppstr &&str);
    cppstr &operator=(cppstr &&str);
    // allocated size
    size_t size() const;
    // number of chars
    size_t length() const;
    /**
     * returns index of first occurance of str
     * or cppstr::npos
     */
    size_t find(const cppstr &str, int offset = 0);
    void append(const cppstr &str);
    const char *c_str() const;
    // append given str starting at given index
    void appendAt(const char *str, int ind);
    // insert given string between substring from up to substring to
    void replaceBetween(const cppstr &str, const cppstr &from, const cppstr &to,
                        bool whole_match = true);
    /**
     * writes the given string into the buffer starting at ind.
     * will realloc if string doesn't fit.
     * Inserts NULL term after writing.
     */
    void overWrite(const cppstr &str, int ind);
    cppstr operator+(const char *c);
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

#endif /* CPPSTR_H */
