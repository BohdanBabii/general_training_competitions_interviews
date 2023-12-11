// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

/************** begin assignment **************/
// The input is an array of n unsigned integers, where A[i] denotes the maximum
// you can advance from index i.
// Write a function to compute the minimum number
// of steps needed to advance beyond the last index of an array. If it's
// impossible to go beyond the last index of an array, your function should
// return 0.
// Optimal: O(n) time, O(1) space

// EXAMPLES
// Input: < 4, 1, 2, 3, 0, 2, 0 >
// Output: 3

// Input: < 4, 1, 2, 3, 0, 1, 0 >

// Output: 0

bool canJump(const vector<size_t> &A) {
    size_t farthest = 0;
    size_t goal = A.size();
    for (size_t i = 0; i < A.size(); i++) {
        if (i > farthest) {
            return false;
        }
        farthest = max(farthest, i + A[i]);
    }
    if (A.size() > farthest) {
        return false;
    }
    return true;
}

size_t min_steps_beyond_last_index(const vector<size_t> &A) {
    size_t ans = 0;
    size_t end = 0;
    size_t farthest = 0;

    if (A.size() == 0 || A.size() == 1 && A[0] == 0) {
        return 0;
    }

    if (canJump(A)) {
        for (size_t i = 0; i < A.size(); ++i) {
            farthest = max(farthest, i + A[i]);
            if (farthest > A.size() - 1) {
                ++ans;
                break;
            }
            if (i == end) {
                ++ans;
                end = farthest;
            }
        }
        return ans;
    } else {
        return 0;
    }
}

/*************** end assignment ***************/

int main() {
    {
        vector<size_t> v;
        assert(min_steps_beyond_last_index(v) == 0);
    }
    {
        vector<size_t> v = {1};
        assert(min_steps_beyond_last_index(v) == 1);
    }
    {
        vector<size_t> v = {0};
        assert(min_steps_beyond_last_index(v) == 0);
    }
    {
        vector<size_t> v = {3, 3, 1, 0, 2, 0, 1};
        assert(min_steps_beyond_last_index(v) == 4);
    }
    {
        vector<size_t> v = {3, 3, 1, 0, 2, 0, 0};
        assert(min_steps_beyond_last_index(v) == 0);
    }
    {
        vector<size_t> v = {3, 2, 0, 0, 2, 0, 1};
        assert(min_steps_beyond_last_index(v) == 0);
    }
    {
        vector<size_t> v = {2, 4, 1, 1, 0, 2, 3};
        assert(min_steps_beyond_last_index(v) == 3);
    }
    {
        vector<size_t> v = {2, 1, 1, 3, 0, 2, 0};
        assert(min_steps_beyond_last_index(v) == 4);
    }
    {
        vector<size_t> v = {4, 1, 2, 3, 0, 1, 0};
        assert(min_steps_beyond_last_index(v) == 0);
    }
    {
        vector<size_t> v = {4, 1, 2, 3, 0, 2, 0};
        assert(min_steps_beyond_last_index(v) == 3);
    }
    {
        vector<size_t> v = {1, 1, 5, 1, 1, 1, 1, 4, 1, 1, 1};
        assert(min_steps_beyond_last_index(v) == 4);
    }
    {
        vector<size_t> v = {3, 0, 0, 4, 1, 1, 1, 4, 1, 1, 1};
        assert(min_steps_beyond_last_index(v) == 3);
    }
    cout << "all tests passed" << endl;
}
