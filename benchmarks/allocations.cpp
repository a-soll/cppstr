#include <chrono>
#include <cppstr/cppstr.h>
#include <vector>

using namespace std::chrono;

// measure std::string vs cppstr::string for SSO allocation
void sso() {
    std::vector<long long> std_results;
    std::vector<long long> cppstr_results;
    constexpr int num_tests = 10;

    // ensure there's no caching being done during tests
    std::string dummy = "short string";
    cppstr::string c_dummy = "short string";

    for (int i = 0; i < num_tests; i++) {
        auto start          = high_resolution_clock::now();
        std::string std_sso = "Short string";
        auto stop           = high_resolution_clock::now();
        auto duration       = duration_cast<nanoseconds>(stop - start);
        std_results.push_back(duration.count());
        std::cout << "std sso allocation: " << duration.count() << '\n';
    }

    for (int i = 0; i < num_tests; i++) {
        auto start                = high_resolution_clock::now();
        cppstr::string cppstr_sso = "Short string";
        auto stop                 = high_resolution_clock::now();
        auto duration             = duration_cast<nanoseconds>(stop - start);
        cppstr_results.push_back(duration.count());
        std::cout << "cppstr sso allocation: " << duration.count() << '\n';
    }

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

    std::cout << "std avg: " << std_avg << '\n';
    std::cout << "cppstr avg: " << cppstr_avg << '\n';
}

int main() {
    sso();
}
