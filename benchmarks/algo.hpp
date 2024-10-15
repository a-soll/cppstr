#include <chrono>

using namespace std::chrono;

template <typename str_type, typename test_object>
int64_t short_append() {
    str_type str = test_object::non_sso_string();
    auto start   = high_resolution_clock::now();
    str.append("more string");
    auto end = high_resolution_clock::now();
    return (end - start).count();
}

template <typename str_type, typename test_object>
int64_t long_append() {
    str_type str = test_object::non_sso_string();
    auto start   = high_resolution_clock::now();
    str.append(test_object::non_sso_string());
    auto end = high_resolution_clock::now();
    return (end - start).count();
}
