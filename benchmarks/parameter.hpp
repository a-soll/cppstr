#include <chrono>

using namespace std::chrono;

// put some logic so compiler doesn't skip function call
template <typename str_type, typename test_object>
inline static void _as_reference(str_type &str) {
    str.append(test_object::non_sso_string());
}

// put some logic so compiler doesn't skip function call
template <typename str_type, typename test_object>
inline static void _as_copy(str_type str) {
    str.append(test_object::non_sso_string());
}

template <typename str_type, typename test_object>
int64_t append_reference() {
    str_type str = test_object::non_sso_string();
    auto start   = high_resolution_clock::now();
    _as_reference<str_type, test_object>(str);
    auto stop = high_resolution_clock::now();
    return (stop - start).count();
}

template <typename str_type, typename test_object>
int64_t append_copy() {
    str_type str = test_object::non_sso_string();
    auto start   = high_resolution_clock::now();
    _as_copy<str_type, test_object>(str);
    auto stop = high_resolution_clock::now();
    return (stop - start).count();
}
