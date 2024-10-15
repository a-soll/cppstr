#include "algo.hpp"
#include "allocation.hpp"
#include "benchmark.hpp"
#include "parameter.hpp"

static constexpr int NUM_TESTS = 999999;

template <typename str_type, typename test_object>
void add_allocation_tests(Benchmark<test_object> &bench) {
    auto group = bench.add_group("allocations");
    group->add_test({"sso", allocation::sso<str_type>});
    group->add_test({"non sso", allocation::non_sso<str_type>});
    group->add_test({"append to sso", allocation::append_to_sso<str_type, test_object>});
    group->add_test(
        {"append to non sso", allocation::append_to_non_sso<str_type, test_object>}
    );
    group->add_test(
        {"consecutive append", allocation::consecutive_appends<str_type, test_object>}
    );
    group->add_test(
        {"exponential append", allocation::exponential_appends<str_type, test_object>}
    );
}

template <typename str_type, typename test_object>
void add_parameter_tests(Benchmark<test_object> &bench) {
    auto group = bench.add_group("parameters");
    group->add_test({"pass reference", append_reference<str_type, test_object>});
    group->add_test({"pass copy", append_copy<str_type, test_object>});
}

template <typename str_type, typename test_object>
void add_all_tests() {
    Benchmark<test_object> bench(NANOSECONDS, NUM_TESTS);

    add_stringview_tests<str_type, test_object>(bench);
    add_allocation_tests<str_type, test_object>(bench);
    add_parameter_tests<str_type, test_object>(bench);

    bench.run_tests();
}
