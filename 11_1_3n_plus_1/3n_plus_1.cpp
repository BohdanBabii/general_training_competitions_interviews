#include <cassert>
#include <iostream>
using namespace std;

int sum(int n) {
    if (n == 1) {
        return 1;
    } else if (n % 2 == 0) {
        return n + sum(n / 2);
    } else {
        return n + sum(3 * n + 1);
    }
}

int main() {
    int n;
    cin >> n;
    int sum_n = sum(n);
    cout << sum_n << endl;

    int example_1 = 6;
    int sum_example_1 = sum(example_1);
    assert(sum_example_1 == 55);

    int example_2 = 5;
    int sum_example_2 = sum(example_2);
    assert(sum_example_2 == 36);

    int example_3 = 10;
    int sum_example_3 = sum(example_3);
    assert(sum_example_3 == 46);

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}