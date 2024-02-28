#include <iostream>

int main() {
    int limit = 1000;

    int sum = 0;
    for (int i = 1; i < limit; ++i) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }

    std::cout << "The sum of multiples of 3 and 5 below " << limit << " is: " << sum << std::endl;

    return 0;
}
