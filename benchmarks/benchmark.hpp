/**
 * https://github.com/a-soll/cpp_benchmarker
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

// vector of each test iteration result
using times = std::vector<uint64_t>;

// alias for test function callback
template <typename T>
using test = std::function<int64_t()>;

// maps string to function
template <typename T>
using test_pair = std::pair<std::string, test<T>>;

template <typename T>
using test_vector = std::vector<test_pair<T>>;

// maps key to series of tests
template <typename T>
using test_group = std::pair<std::string, test_vector<T>>;

template <typename T>
using groups = std::vector<test_group<T>>;

namespace Color {
enum Code {
    FG_RED     = 31,
    FG_GREEN   = 32,
    FG_YELLOW  = 33,
    FG_BLUE    = 34,
    FG_DEFAULT = 39,
    BG_RED     = 41,
    BG_GREEN   = 42,
    BG_BLUE    = 44,
    BG_DEFAULT = 49
};
class Modifier {
    Code code;

public:
    Modifier(Code pCode)
        : code(pCode) {}
    friend std::ostream &operator<<(std::ostream &os, const Modifier &mod) {
        return os << "\033[" << mod.code << "m";
    }
};
} // namespace Color

enum benchmark_unit {
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECONDS
};

template <typename T>
class Benchmark {
public:
    class Group {
    public:
        friend class Benchmark<T>;
        Group(std::string_view name)
            : _name(name) {}

        void add_test(test_pair<T> test) {
            this->_tests.push_back(test);
            this->_max_len = std::max<int64_t>(test.first.length(), this->_max_len);
        }

    private:
        std::string _name;
        test_vector<T> _tests;
        size_t _max_len = 0;
    };

    Benchmark<T>(benchmark_unit unit, uint64_t num_tests)
        : _num_tests(num_tests) {
        switch (unit) {
        case SECONDS:
            this->_unit = "s";
        case MILLISECONDS:
            this->_unit = "ms";
        case MICROSECONDS:
            this->_unit = "us";
        case NANOSECONDS:
        default:
            this->_unit = "ns";
        }
    }

    void add_test(test_pair<T> test) {
        this->_output.clear();
        this->_max_len = std::max<int64_t>(test.first.length(), this->_max_len);
        this->_tests.push_back(std::move(test));
    }

    Group *add_group(std::string_view group_name) {
        this->_groups.push_back(Group(group_name));
        return &this->_groups.back();
    }

    void run_tests() {
        this->_times.clear();
        std::cout << Color::Modifier(Color::FG_DEFAULT) << T::name
                  << Color::Modifier(Color::FG_DEFAULT) << '\n';
        std::cout << "-----------------------------\n";
        this->_run_groups();
        for (auto &t : this->_tests) {
            this->_run_test(t, this->_max_len);
            this->_print_output();
        }
        this->_max_len = 0;
        this->_tests.clear();
    }

private:
    std::vector<int64_t> _results;
    times _times;
    test_vector<T> _tests;
    std::string _output;
    int64_t _max_len = 0; // used for formatting output
    std::string _unit;
    uint64_t _num_tests;
    std::string _indent = "--";
    std::vector<Group> _groups;

    uint64_t _get_avg() {
        uint64_t avg = 0;
        for (auto &i : this->_times) {
            avg += i;
        }
        return avg = avg / this->_times.size();
    }

    void _print_output() {
        std::cout << this->_output << this->_unit << "\n";
        this->_output.clear();
        this->_times.clear();
    }

    void _run_test(test_pair<T> &p, size_t max_len) {
        // for (auto &p : tests) {
        this->_output += p.first;
        for (int i = p.first.length(); i < max_len + 2;
             i++) { // this can't be the best way
            this->_output += ' ';
        }
        for (int i = 0; i < this->_num_tests; i++) {
            this->_times.push_back(p.second());
        }
        this->_output += std::to_string(this->_get_avg());
    }

    void _run_groups() {
        for (auto &g : this->_groups) {
            std::cout << Color::Modifier(Color::FG_RED) << g._name
                      << Color::Modifier(Color::FG_DEFAULT) << '\n';
            for (auto &t : g._tests) {
                this->_run_test(t, g._max_len);
                std::cout << this->_indent << ' ';
                this->_print_output();
            }
            std::cout << '\n';
        }
    }
};

#endif /* OUTPUT_H */
