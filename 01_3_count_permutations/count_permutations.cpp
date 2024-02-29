// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

// C++ program to illustrate
// std :: unordered_map :: at()
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/************** begin assignment **************/
// given a smaller string s and a bigger string b, design an algorithm to count
// all permutation appearances of the shorter string within the longer string
// assumption: only the 26 characters from a to z are allowed in both strings
//
// example:
// s = abbc
// b = cbabadcbbabbcba
//     cbab
//           cbba
//              abbc
//                bcba
// answer: permutations of the shorter string s
//         appear 4 times in the longer string b

// An obvious brute force solution is to generate all permutations of s and then
// look for each in b. Since there are S! permutations, this will take O(S! * B)
// time, where S is the length of s and B is the length of b. This works, but
// it's an extraordinarily slow algorithm. It's actually worse than an
// exponential algorithm. If s has 14 characters, that's over 87 billion
// permutations. Add one more character into s and we have 15 times more
// permutations. -->  implement an algorithm that needs at most O(B * S^2) time
//
// Before you start coding: Try to find the places where the permutations appear
// on your own. Observe how you do this. This will help you to develop a decent
// algorithm quite easily.

int count_permutations(const string &s, const string &b) {
    int count = 0;

    // TODO: given a smaller string s and a bigger string b, design an algorithm
    //  that needs at most O(B * S^2) time to count all permutation appearances
    //  of the shorter string within the longer string
    unordered_map<char, int> mp;  // Use hashmap to store the frequencies of all the characters present in string s1.
    for (auto it : s) {
        mp[it]++;
    }
    int countSize = mp.size();  // Use the count variable to see if all of the characters in the map have the same frequency, indicating that an anagram has been found.
    int i = 0, j = 0;

    int k = s.size();  // Window Size
    if (s == "") {
        return 0;
    }

    while (j < b.size()) {
        if (mp.find(b[j]) != mp.end()) {  // If a character is found that already exists in the map, reduce its frequency by one.
            mp[b[j]]--;
            if (mp[b[j]] == 0) {  // If the frequency of a specific character on the map is 0, it means that all occurrences of that character is found inside the current window size.
                countSize--;
            }
        }
        if (j - i + 1 < k) {
            j++;
        } else if (j - i + 1 == k) {
            if (countSize == 0) {  // Anagram found
                count++;
            }
            if (mp.find(b[i]) != mp.end()) {  // Check if that character is present in the map while sliding the window, then increase its frequency by one, as we decreased its frequency when we first met it while crossing the window.
                mp[b[i]]++;
                if (mp[b[i]] == 1) {
                    countSize++;
                }
            }
            i++;
            j++;
        }
    }

    return count;
}

/*************** end assignment ***************/

int main() {
    // longer string is not a permutation of shorter string
    assert(count_permutations("cbabadcbbabbcba", "abbc") == 0);

    assert(count_permutations("xyz", "xyz") == 1);
    assert(count_permutations("xyz", "xzy") == 1);

    // no common permutations

    assert(count_permutations("abzc", "cbabadcbbabbcba") == 0);
    assert(count_permutations("", "cbabadcbbabbcba") == 0);
    assert(count_permutations("cbabadcbbabbcba", "") == 0);

    assert(count_permutations("abbc", "cbabadcbbabbcba") == 4);
    assert(count_permutations("abbc", "cbabadcbbabbcbabaabccbabc") == 7);

    string s = "cat";
    string b =
        "ydwztctaaaatxocabnpgcircgysctattacqtklzypxzqtvmwejcbvqhgljulsopnldoifefp"
        "kjnvipxkfnamdsacaxosactbrnioabfxixseyetzackxhmuqnpjwfzesjwktacatfqlxxmqb"
        "jnaceobxyvqahrjdofrdhhciatcgaoueybnqsklwhfkzvltcaiacty";

    assert(count_permutations(s, b) == 9);

    // some longer word
    s = "Psychotomimetic";
    b = "PsychoxtomimetiPsycotomimehticcunyaschPoetcomyimtixkjnvipxkfnamdsacaxosa"
        "ctbrnioabfxixseyetzackxhmuqunyaschePocomtyimti";

    assert(count_permutations(s, b) == 3);

    cout << "all tests passed" << endl;
}
