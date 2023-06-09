#ifndef CPPSTR_H
#define CPPSTR_H

#include <iostream>
#include <string>

class cppstr {
    friend std::ostream &operator<<(std::ostream &s, const cppstr &cppstr);
  public:
    void operator+=(const char *rhs);
    void operator+=(char rhs);
    cppstr &operator=(const char *rhs);
    cppstr &operator=(const std::string &rhs);
    bool operator==(const std::string &rhs) const;
    bool operator==(const cppstr &rhs) const;
    bool operator==(const char *rhs) const;
    cppstr operator+(const char *rhs) const;
    operator std::string();
    operator std::string &();
    char &operator[](int index);
    char &operator[](int index) const;

    cppstr(const char *str);
    cppstr(const std::string &str);
    cppstr();
    ~cppstr();
    /**
     * Replace substr in CppStr with given string
     * ex assuming string is "X {} X":
     * replace("{}", "inserting") -> "X inserting X"
     */
    void replace(const char *repl, const char *with);
    /**
     * Insert given string between substring
     * ex assuming string is "X {} X":
     * replaceBetween("{", "}", "inserting") -> "X {inserting} X"
     */
    void replaceBetween(const char *start, const char *end, const char *with);
    size_t length() const;
    // return std::string representation to access std functions
    std::string &toString() const;
    void append(const char *str);
    void append(const std::string &str);
    void append(const cppstr &str);
  private:
    std::string *_internal;
};

#endif /* CPPSTR_H */
