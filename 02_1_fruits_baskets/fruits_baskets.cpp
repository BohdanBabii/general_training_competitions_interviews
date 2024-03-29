// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// helper macros for timings
#define TIMERSTART(label)                                                  \
    std::chrono::time_point<std::chrono::system_clock> a##label, b##label; \
    a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                        \
    b##label = std::chrono::system_clock::now();                                \
    std::chrono::duration<double> delta##label = b##label - a##label;           \
    std::cout << #label << ": " << std::setprecision(4) << delta##label.count() \
              << " seconds" << std::endl;

// parse input file and create baskets vector
vector<set<string>> get_baskets(const string &file_name) {
    ifstream ifs(file_name);
    if (ifs.fail()) {
        cerr << "failed to open " << file_name << endl;
        exit(-1);
    }
    string line;
    string word;
    vector<set<string>> baskets;
    while (getline(ifs, line)) {
        stringstream iss(line);
        set<string> basket;
        while (iss >> word)
            basket.insert(word);
        baskets.push_back(basket);
    }
    return baskets;
}

// count the common items between two sets of words
size_t intersection_count(const set<string> &b1, const set<string> &b2) {
    vector<string> v;
    set_intersection(begin(b1), end(b1), begin(b2), end(b2),
                     std::back_inserter(v));
    return v.size();
}

/************** begin assignment **************/
// The "vector baskets" contains 5000 baskets of fruits, for example baskets[5]
// contains the following fruits {Coconut, Watermelon, Apricot}.
// The "vector preferences" contains preferences for fruits of 1000 people, for
// example the person in preferences[2] prefers {Strawberry, Melon, Avocado,
// Jackfruit}. Count the baskets for each person that have at least 3 fruits of
// a person's preferences. A basket can contain 3 to 7 different (unique)
// fruits. Also the preferences of the persons are between 3 to 7 different
// (unique) fruits. There are only 28 different fruits.

// A naive solution uses sets of strings to compute intersections between
// baskets and preferences.
// It also iterates over all baskets for each user.
vector<size_t> count_matches_naive(const vector<set<string>> &baskets,
                                   const vector<set<string>> &preferences) {
    // matches_count contains the matches count for each person
    vector<size_t> matches_count(
        preferences.size());  // create vector of all zeros
    // iterate over all persons
    for (size_t i = 0; i < preferences.size(); ++i) {
        // iterate over all possible baskets
        for (const auto &basket : baskets) {
            // if a basket contains at least 3 fruits of a person's preferences, then
            // we have a match
            if (intersection_count(preferences[i], basket) >= 3) {
                matches_count[i]++;
            }
        }
    }
    return matches_count;
}
std::map<std::string, int> fruit_bits = {
    {"Apple", 0b1},
    {"Apricot", 0b10},
    {"Avocado", 0b100},
    {"Banana", 0b1000},
    {"Blueberry", 0b10000},
    {"Cherry", 0b100000},
    {"Coconut", 0b1000000},
    {"Grape", 0b10000000},
    {"Grapefruit", 0b100000000},
    {"Jackfruit", 0b1000000000},
    {"Kiwi", 0b10000000000},
    {"Lemon", 0b100000000000},
    {"Lime", 0b1000000000000},
    {"Mango", 0b10000000000000},
    {"Melon", 0b100000000000000},
    {"Mandarin", 0b1000000000000000},
    {"Nectarine", 0b10000000000000000},
    {"Orange", 0b100000000000000000},
    {"Papaya", 0b1000000000000000000},
    {"Peach", 0b10000000000000000000},
    {"Pear", 0b100000000000000000000},
    {"Pineapple", 0b1000000000000000000000},
    {"Plum", 0b10000000000000000000000},
    {"Pomegranate", 0b100000000000000000000000},
    {"Raspberry", 0b1000000000000000000000000},
    {"Strawberry", 0b10000000000000000000000000},
    {"Starfruit", 0b100000000000000000000000000},
    {"Watermelon", 0b1000000000000000000000000000}};

// TODO: implement a "fast matches counter" using bit operations
// Voluntary (not required): If you are really interested in speeding up the
// code, also develop a strategy to avoid iterating over all the baskets each
// time. (In a real speed competition this would be essential for winning!)
vector<size_t> count_matches_fast(const vector<set<string>> &baskets,
                                  const vector<set<string>> &preferences) {
    vector<size_t> matches_count(preferences.size());
    vector<bitset<28>> basket_bitset(baskets.size());
    vector<bitset<28>> preferences_bitset(preferences.size());

    for (size_t i = 0; i < baskets.size(); ++i) {
        for (const auto &fruit : baskets[i]) {
            basket_bitset[i] |= fruit_bits[fruit];
        }
    }

    for (size_t i = 0; i < preferences.size(); ++i) {
        for (const auto &fruit : preferences[i]) {
            preferences_bitset[i] |= fruit_bits[fruit];
        }
    }

    for (size_t i = 0; i < preferences.size(); ++i) {
        for (size_t j = 0; j < baskets.size(); ++j) {
            if ((preferences_bitset[i] & basket_bitset[j]).count() >= 3) {
                matches_count[i]++;
            }
        }
    }

    return matches_count;
}
/*************** end assignment ***************/

int main() {
    vector<set<string>> baskets = get_baskets("baskets.txt");
    vector<set<string>> preferences = get_baskets("preferences.txt");

    TIMERSTART(naive)
    auto results_naive = count_matches_naive(baskets, preferences);
    TIMERSTOP(naive)

    TIMERSTART(fast)
    auto results_fast = count_matches_fast(baskets, preferences);
    TIMERSTOP(fast)

    assert(results_naive == results_fast);

    cout << "all tests passed" << endl;
}
