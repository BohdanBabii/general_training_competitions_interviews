#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void dfs(char node, unordered_set<char>& visited, const unordered_map<char, unordered_set<char>>& graph) {
    visited.insert(node);
    for (char neighbor : graph.at(node)) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, visited, graph);
        }
    }
}

int countMaxSubgraphs(const unordered_map<char, unordered_set<char>>& graph) {
    unordered_set<char> visited;
    int count = 0;

    for (const auto& entry : graph) {
        char node = entry.first;
        if (visited.find(node) == visited.end()) {
            count++;
            dfs(node, visited, graph);
        }
    }

    return count;
}

int main() {
    int numCases;
    cin >> numCases;
    cin.ignore();  // Consume the newline character after numCases

    for (int caseNum = 0; caseNum < numCases; ++caseNum) {
        if (caseNum > 0) {
            cout << endl;
        }

        char largestNode;
        cin >> largestNode;
        cin.ignore();

        unordered_map<char, unordered_set<char>> graph;
        vector<string> edges;

        while (true) {
            string line;
            getline(cin, line);
            if (line.empty()) {
                break;
            }
            edges.push_back(line);
        }

        for (const string& edge : edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }

        int result = countMaxSubgraphs(graph);
        cout << result << endl;
    }

    // Test Case 1
    int result1 = countMaxSubgraphs({{'A', {'B', 'E'}}, {'B', {'A', 'C'}}, {'C', {'B', 'D'}}, {'D', {'C', 'E'}}, {'E', {'D', 'A'}}});
    assert(result1 == 1);

    // Test Case 2
    int result2 = countMaxSubgraphs({{'A', {'B', 'D'}}, {'B', {'A', 'C'}}, {'C', {'B', 'D'}}, {'D', {'A', 'C'}}});
    assert(result2 == 1);

    // Test Case 3
    int result3 = countMaxSubgraphs({{'X', {'Y', 'Z'}}, {'Y', {'X', 'Z'}}, {'Z', {'X', 'Y'}}, {'U', {'V'}}, {'V', {'U', 'W'}}, {'W', {'V'}}});
    assert(result3 == 2);

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
