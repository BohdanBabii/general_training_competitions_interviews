#include <cassert>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<vector<int>> getMatrix(const string &file) {
    ifstream ifs(file);
    if (!ifs.is_open()) {
        cerr << "Error " << file << endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<int>> matrix;
    string line;

    while (getline(ifs, line)) {
        istringstream iss(line);
        vector<int> pairs;

        string value;
        while (getline(iss, value, ',')) {
            int num = (value == "-") ? 0 : stoi(value);
            pairs.push_back(num);
        }

        matrix.push_back(pairs);
    }

    return matrix;
}

vector<vector<int>> getMinSpanTree(const vector<vector<int>> &adjacencyMatrix) {
    size_t n = adjacencyMatrix.size();
    vector<vector<int>> minSpanTree(n, vector<int>(n, 0));
    unordered_set<size_t> visited;
    queue<size_t> bfsQueue;

    bfsQueue.push(0);
    visited.insert(0);

    while (!bfsQueue.empty()) {
        size_t curVert = bfsQueue.front();
        bfsQueue.pop();

        for (size_t neighbor = 0; neighbor < n; ++neighbor) {
            if (adjacencyMatrix[curVert][neighbor] != 0 && visited.find(neighbor) == visited.end()) {
                minSpanTree[curVert][neighbor] = adjacencyMatrix[curVert][neighbor];
                minSpanTree[neighbor][curVert] = adjacencyMatrix[curVert][neighbor];
                visited.insert(neighbor);
                bfsQueue.push(neighbor);
            }
        }
    }

    return minSpanTree;
}
void printMatrix(vector<vector<int>> matrix) {
    for (auto row : matrix) {
        for (auto k : row)
            cout << k << " ";
        cout << endl;
    }
    cout << endl;
}

bool compareMatrices(const vector<vector<int>> &matrix1, const vector<vector<int>> &matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1.empty() || matrix1[0].size() != matrix2[0].size()) {
        // Matrices have different dimensions
        return false;
    }

    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[i].size(); ++j) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    string file = "network.txt";
    vector<vector<int>> network = getMatrix(file);
    printMatrix(network);
    vector<vector<int>> minSpanTree = getMinSpanTree(network);
    printMatrix(minSpanTree);
    return 0;
}