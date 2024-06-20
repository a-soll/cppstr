#ifndef HELPER_H
#define HELPER_H

#include <cppstr/cppstr.h>
#include <vector>

extern std::vector<long long> std_results;
extern std::vector<long long> cppstr_results;
constexpr int num_tests = 10;

void print_avg(const cppstr::string &test_name);
void reset_results();

#endif /* HELPER_H */
