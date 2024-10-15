#include <chrono>
#include <cppstr/cppstr.h>

using namespace std::chrono;

namespace allocation {

template <typename T>
int64_t sso() {
    auto start = high_resolution_clock::now();
    T sso      = "SSO string";
    auto stop  = high_resolution_clock::now();
    return (stop - start).count();
}

template <typename str_type>
int64_t non_sso() {
    auto start = high_resolution_clock::now();
    str_type non_sso =
        "non sso non sso non sso non sso non sso non sso non sso non sso non sso "
        "non sso non sso non sso non sso non sso non sso non sso non sso non sso "
        "non sso non sso non sso non sso non sso non sso non sso non sso ";
    auto stop = high_resolution_clock::now();
    return (stop - start).count();
}

template <typename str_type, typename test_object>
int64_t append_to_sso() {
    str_type sso = test_object::sso_string();
    auto start   = high_resolution_clock::now();
    sso.append(test_object::non_sso_string());
    auto stop = high_resolution_clock::now();
    return (stop - start).count();
}

template <typename str_type, typename test_object>
int64_t append_to_non_sso() {
    test_object object;
    str_type non_sso = test_object::non_sso_string();
    auto start       = high_resolution_clock::now();
    non_sso.append(test_object::non_sso_string());
    auto stop = high_resolution_clock::now();
    return (stop - start).count();
}

template <typename str_type, typename test_object>
int64_t consecutive_appends() {
    str_type str = test_object::non_sso_string();
    auto start   = high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        str.append(test_object::non_sso_string());
    }
    auto end = high_resolution_clock::now();
    return (end - start).count();
}

template <typename str_type, typename test_object>
int64_t exponential_appends() {
    str_type str = test_object::non_sso_string();
    auto start   = high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        str.append(str);
    }
    auto end = high_resolution_clock::now();
    return (end - start).count();
}

} // namespace allocation
