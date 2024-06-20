#include "helper.h"
#include <cppstr/cppstr.h>

using namespace std::chrono;

static bool cpp_as_ref(const cppstr::string &s) {
    // bool match = s == "test";
    bool match = false;
    return match;
}

static bool std_as_ref(const std::string &s) {
    // bool match = s == "test";
    bool match = false;
    return match;
}

static bool cpp_as_copy(cppstr::string s) {
    // bool match = s == "test";
    bool match = false;
    return match;
}

static bool std_as_copy(std::string s) {
    // bool match = s == "test";
    bool match = false;
    return match;
}

static void const_ref() {
    reset_results();
    for (int i = 0; i < num_tests; i++) {
        std::string std = "This is a test string";
        auto start = high_resolution_clock::now();
        std_as_ref(std);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        std_results.push_back(duration.count());
    }

    for (int i = 0; i < num_tests; i++) {
        cppstr::string cpp = "This is a test string";
        auto start = high_resolution_clock::now();
        cpp_as_ref(cpp);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cppstr_results.push_back(duration.count());
    }
    print_avg("const ref");
}

static void copy() {
    reset_results();
    for (int i = 0; i < num_tests; i++) {
        std::string std = "This is a test string";
        auto start = high_resolution_clock::now();
        std_as_copy(std);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        std_results.push_back(duration.count());
    }

    for (int i = 0; i < num_tests; i++) {
        cppstr::string cpp = "This is a test string";
        auto start = high_resolution_clock::now();
        cpp_as_copy(cpp);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cppstr_results.push_back(duration.count());
    }
    print_avg("copy");
}

void run_parameter() {
    const_ref();
    copy();
}
