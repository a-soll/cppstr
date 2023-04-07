#include <iostream>
#include <string>

class CppStr {
    friend std::ostream &operator<<(std::ostream &s, const CppStr &cppstr);
  public:
    void operator+=(std::string rhs);
    CppStr operator+(std::string rhs);
    std::string str;
    CppStr(std::string str);
    /**
     * Replace substr in CppStr with given string
     * ex assuming string is "X {} X":
     * replace("{}", "inserting") -> "X inserting X"
     */
    void replace(std::string repl, std::string with);
    /**
     * Insert given string between substring
     * ex assuming string is "X {} X":
     * replaceBetween("{", "}", "inserting") -> "X {inserting} X"
     */
    void replaceBetween(std::string start, std::string end, std::string with);
};
