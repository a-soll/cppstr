#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include <cppstr/cppstr.h>
#include <string>

class CppStrTest {
public:
    CppStrTest() {}

    inline static const std::string name = "cppstr::string";

    static inline cppstr::string sso_string() {
        return "sso";
    }

    static inline cppstr::string non_sso_string() {
        return "non sso non sso non sso non sso non sso non sso non sso non sso non sso "
               "non sso non sso non sso non sso non sso non sso non sso non sso non sso "
               "non sso non sso non sso non sso non sso non sso non sso non sso ";
    }
};

class StdStrTest {
public:
    StdStrTest() {}

    inline static const std::string name = "std::string";

    static inline std::string sso_string() {
        return "sso";
    }

    static inline std::string non_sso_string() {
        return "non sso non sso non sso non sso non sso non sso non sso non sso non sso "
               "non sso non sso non sso non sso non sso non sso non sso non sso non sso "
               "non sso non sso non sso non sso non sso non sso non sso non sso ";
    }
};

#endif /* TEST_OBJECT_H */
