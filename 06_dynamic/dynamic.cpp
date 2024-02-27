// Dynamic programming is a very important problem solving strategy in
// competitive programming problems.
//
// In the backtracking assignment you had to work with code you didn't write.
// In this assignment you write everything yourself from the beginning.
//
// TODO: Read chapter 7 from the "Competitive Programmer’s Handbook"
// https://cses.fi/book/book.pdf --> pp. 65 - 76
// TODO: Choose one of the three following problems presented in the book:
//       - Longest increasing subsequence
//       - Paths in a grid
//       - Knapsack (all possible sums)
//       Implement for your chosen problem with dynamic programming
//       1. an iterative solution
//                and
//       2. a recursive solution
//       Test your implementations thoroughly. Start by writing your test cases
//       before you implement the algorithms.
//       Document your solutions thoroughly by writing meaningful comments.

#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

// Function to find the length of the longest increasing subsequence in a given vector of integers.
// Uses dynamic programming to solve the problem.
// Returns the length of the longest increasing subsequence.
int lengthOfLIS(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int n = nums.size();
    std::vector<int> dp(n, 1);

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }

    return *std::max_element(dp.begin(), dp.end());
}

// Helper function for the recursive solution of finding the length of the longest increasing subsequence.
// Takes a vector of integers, the current index, and the previous element as parameters.
// Returns the length of the longest increasing subsequence starting from the current index.
int helper(std::vector<int>& nums, int i, int prev) {
    if (i == nums.size()) {
        return 0;
    }

    int taken = 0;
    if (nums[i] > prev) {
        taken = 1 + helper(nums, i + 1, nums[i]);
    }

    int notTaken = helper(nums, i + 1, prev);

    return std::max(taken, notTaken);
}

int lengthOfLISRecur(std::vector<int>& nums) {
    return helper(nums, 0, INT_MIN);
}
int main() {
    std::unordered_map<int, int> memo;
    {
        std::vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
        assert(lengthOfLIS(nums) == 4);
        assert(lengthOfLISRecur(nums) == 4);
    }
    {
        std::vector<int> nums{0, 1, 0, 3, 2, 3};
        assert(lengthOfLIS(nums) == 4);
        assert(lengthOfLISRecur(nums) == 4);
    }
    {
        std::vector<int> nums{7, 7, 7, 7, 7, 7, 7};
        assert(lengthOfLIS(nums) == 1);
        assert(lengthOfLISRecur(nums) == 1);
    }
    {
        std::vector<int> nums{1, 3, 6, 7, 9, 4, 10, 5, 6};
        assert(lengthOfLIS(nums) == 6);
        assert(lengthOfLISRecur(nums) == 6);
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
        assert(lengthOfLIS(nums) == 9);
        assert(lengthOfLISRecur(nums) == 9);
    }
    {
        std::vector<int> nums{9, 8, 7, 6, 5, 4, 3, 2, 1};
        assert(lengthOfLIS(nums) == 1);
        assert(lengthOfLISRecur(nums) == 1);
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        assert(lengthOfLIS(nums) == 9);
        assert(lengthOfLISRecur(nums) == 9);
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        assert(lengthOfLIS(nums) == 9);
        assert(lengthOfLISRecur(nums) == 9);
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        assert(lengthOfLIS(nums) == 9);
        assert(lengthOfLISRecur(nums) == 9);
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        assert(lengthOfLIS(nums) == 9);
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        assert(lengthOfLIS(nums) == 9);
    }
    {
        std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                              1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        assert(lengthOfLIS(nums) == 9);
    }
    std::cout << "all tests passed" << std::endl;
    return 0;
}
