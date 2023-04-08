#include <iostream>
#include <string>

class cppstr {
    friend std::ostream &operator<<(std::ostream &s, const cppstr &cppstr);
  public:
    void operator+=(const char *rhs);
    void operator=(const char *rhs);
    void operator=(std::string rhs);
    cppstr operator+(const char *rhs);
    operator std::string();
    operator std::string &();

    cppstr(const char *str);
    cppstr(std::string str);
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
    size_t length();
  private:
    std::string *_internal;
};
