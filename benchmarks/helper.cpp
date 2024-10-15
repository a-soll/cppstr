#include "helper.h"

std::vector<long long> std_results;
std::vector<long long> cppstr_results;

void print_avg(const cppstr::string &test_name) {
    long long std_avg    = 0;
    long long cppstr_avg = 0;

    for (auto i : std_results) {
        std_avg += i;
    }
    std_avg = std_avg / std_results.size();

    for (auto i : cppstr_results) {
        cppstr_avg += i;
    }
    cppstr_avg = cppstr_avg / cppstr_results.size();

    std::cout << "====== " << test_name << " ======\n";
    std::cout << "std avg:    " << std_avg << " ns" << '\n';
    std::cout << "cppstr avg: " << cppstr_avg << " ns" << "\n\n";
}

void reset_results() {
    std_results.clear();
    cppstr_results.clear();
}
