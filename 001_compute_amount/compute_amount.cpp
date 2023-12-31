// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// helper macros for timing
#define TIMERSTART(label)                                                  \
    std::chrono::time_point<std::chrono::system_clock> a##label, b##label; \
    a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                              \
    b##label = std::chrono::system_clock::now();                      \
    std::chrono::duration<double> delta##label = b##label - a##label; \
    std::cout << #label << ": " << delta##label.count() << " seconds" \
              << std::endl;

/************** begin assignment **************/
// compute the amount of all positive integer solutions to the equation
// a^3 + b^3 = c^3 + d^3 where a, b, c, and d are integers between 1 and n
// (1 <= n <= 500)

// an obvious brute force solution will just have four nested for loops
// this algorithm iterates through all possible values of a, b, c, and d
// and checks if that combination happens to work --> runtime is O(n^4)
int compute_amount_brute_force(const int n) {
    int amount = 0;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            for (int c = 1; c <= n; ++c) {
                for (int d = 1; d <= n; ++d) {
                    if (a * a * a + b * b * b == c * c * c + d * d * d) {
                        ++amount;
                    }
                }
            }
        }
    }
    return amount;
}

// try to improve the time complexity
// (if you can't, try at least to improve the execution time)
int compute_amount(const int n) {
    int amount = 0;
    std::map<int, std::vector<std::pair<int, int>>> cubeMap;

    // Compute the amount of all positive integer solutions in less
    // than O(n^4) runtime (you can use additional memory)

    for (int c = 1; c <= n; ++c) {
        for (int d = 1; d <= n; ++d) {
            int result = c * c * c + d * d * d;
            cubeMap[result].emplace_back(c, d);
        }
    }

    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            int result = a * a * a + b * b * b;
            auto it = cubeMap.find(result);
            if (it != cubeMap.end()) {
                const auto &pairs = it->second;
                for (const auto &pair : pairs) {
                    // std::cout << a << " " << b << " " << pair.first << " " << pair.second << std::endl;
                    ++amount;
                }
            }
        }
    }

    return amount;
}
/*************** end assignment ***************/

int main() {
    // test correctness of implementation
    for (int n = 1; n < 100; ++n) {
        assert(compute_amount_brute_force(n) == compute_amount(n));
    }

    // compare execution times for n = 500
    int n = 500;
    cout << "n = " << n << endl;
    TIMERSTART(brute_force)
    int result_bf = compute_amount_brute_force(n);
    TIMERSTOP(brute_force)

    TIMERSTART(improved)
    int result = compute_amount(n);
    TIMERSTOP(improved)

    assert(result_bf == result);
}
