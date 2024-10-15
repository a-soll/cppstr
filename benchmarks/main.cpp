#include "test_main.hpp"
#include "test_object.h"

int main() {
    add_all_tests<cppstr::string, CppStrTest>();
    add_all_tests<std::string, StdStrTest>();
}
