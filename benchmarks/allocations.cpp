#include "helper.h"
#include <chrono>
#include <cppstr/cppstr.h>
#include <vector>

using namespace std::chrono;

// measure std::string vs cppstr::string for SSO allocation
static void sso() {
    reset_results();
    // ensure there's no caching being done during tests
    std::string dummy = "short string";
    cppstr::string c_dummy = "short string";

    for (int i = 0; i < num_tests; i++) {
        auto start = high_resolution_clock::now();
        std::string std_sso = "Short string";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        std_results.push_back(duration.count());
        // std::cout << "std sso allocation: " << duration.count() << '\n';
    }

    for (int i = 0; i < num_tests; i++) {
        auto start = high_resolution_clock::now();
        cppstr::string cppstr_sso = "Short string";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cppstr_results.push_back(duration.count());
        // std::cout << "cppstr sso allocation: " << duration.count() << '\n';
    }
    print_avg("sso");
}

static void non_sso() {
    reset_results();
    // ensure there's no caching being done during tests
    std::string dummy = "Non SSO string Non SSO string Non SSO string Non SSO string Non "
                        "SSO string Non SSO string Non SSO string Non SSO string";
    cppstr::string c_dummy =
        "Non SSO string Non SSO string Non SSO string Non SSO string Non SSO string Non "
        "SSO string Non SSO string Non SSO string";

    for (int i = 0; i < num_tests; i++) {
        auto start = high_resolution_clock::now();
        std::string std_sso =
            "Non SSO string Non SSO string Non SSO string Non SSO string Non SSO string "
            "Non SSO string Non SSO string Non SSO string";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        std_results.push_back(duration.count());
        // std::cout << "std sso allocation: " << duration.count() << '\n';
    }

    for (int i = 0; i < num_tests; i++) {
        auto start = high_resolution_clock::now();
        cppstr::string cppstr_sso =
            "Non SSO string Non SSO string Non SSO string Non SSO string Non SSO string "
            "Non SSO string Non SSO string Non SSO string";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cppstr_results.push_back(duration.count());
        // std::cout << "cppstr sso allocation: " << duration.count() << '\n';
    }
    print_avg("non sso");
}

static void append() {
    reset_results();
    std::string dummy = "this is a test string";
    dummy.append("This is more test stringThis is more test stringThis is more test "
                 "stringThis is more test stringThis is more test stringThis is more "
                 "test stringThis is more test string");

    cppstr::string dummy_cpp = "This is a test string";
    dummy_cpp.append("This is more test stringThis is more test stringThis is more test "
                     "stringThis is more test stringThis is more test stringThis is more "
                     "test stringThis is more test string");

    for (int i = 0; i < num_tests; i++) {
        std::string std = "This is a test string";
        auto start = high_resolution_clock::now();
        std.append("This is more test stringThis is more test stringThis is more test "
                   "stringThis is more test stringThis is more test stringThis is more "
                   "test stringThis is more test string");
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        // std::cout << "std append: " << duration.count() << '\n';
        std_results.push_back(duration.count());
    }

    for (int i = 0; i < num_tests; i++) {
        cppstr::string cpp = "This is a test string";
        auto start = high_resolution_clock::now();
        cpp.append("This is more test stringThis is more test stringThis is more test "
                   "stringThis is more test stringThis is more test stringThis is more "
                   "test stringThis is more test string");
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        // std::cout << "cpp append: " << duration.count() << '\n';
        cppstr_results.push_back(duration.count());
    }
    print_avg("append");
}

static void consecutive_appends() {
    reset_results();
    std::string dummy = "this is a test string";
    dummy.append("This is more test stringThis is more test stringThis is more test "
                 "stringThis is more test stringThis is more test stringThis is more "
                 "test stringThis is more test string");

    cppstr::string dummy_cpp = "This is a test string";
    dummy_cpp.append("This is more test stringThis is more test stringThis is more test "
                     "stringThis is more test stringThis is more test stringThis is more "
                     "test stringThis is more test string");

    for (int i = 0; i < num_tests; i++) {
        std::string std = "This is a test string";
        auto start = high_resolution_clock::now();
        std.append("This is more test stringThis is more test stringThis is more test "
                   "stringThis is more test stringThis is more test stringThis is more "
                   "test stringThis is more test string");
        std.append(std);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        std_results.push_back(duration.count());
    }

    for (int i = 0; i < num_tests; i++) {
        cppstr::string cpp = "This is a test string";
        auto start = high_resolution_clock::now();
        cpp.append("This is more test stringThis is more test stringThis is more test "
                   "stringThis is more test stringThis is more test stringThis is more "
                   "test stringThis is more test string");
        cpp.append(cpp);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cppstr_results.push_back(duration.count());
    }
    print_avg("consecutive appends");
}

void run_allocations() {
    sso();
    non_sso();
    append();
    consecutive_appends();
}
