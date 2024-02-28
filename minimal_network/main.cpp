#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<vector<int>> getMatrix(const string &file) {
    ifstream ifs(file);
    if (!ifs.is_open()) {
        cerr << "Error: failed to open " << file << endl;
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

vector<vector<int>> prim_minimal_spanning_tree(const vector<vector<int>> &network) {
    int n = network.size();
    vector<vector<int>> minimal_network(n, vector<int>(n, 0));
    unordered_map<int, bool> visited_vertices;

    int vertex = 0;
    visited_vertices[vertex] = true;

    while (visited_vertices.size() < n) {
        int min = numeric_limits<int>::max();
        int minVertex;

        for (auto &entry : visited_vertices) {
            int v = entry.first;
            for (int i = 0; i < n; i++) {
                if (!visited_vertices[i] && network[v][i] != 0 && network[v][i] < min) {
                    min = network[v][i];
                    minVertex = i;
                }
            }
        }

        visited_vertices[minVertex] = true;

        minimal_network[vertex][minVertex] = network[vertex][minVertex];
        minimal_network[minVertex][vertex] = network[minVertex][vertex];

        vertex = minVertex;
    }

    return minimal_network;
}

void print_matrix(vector<vector<int>> matrix) {
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
    print_matrix(network);
    return 0;
}