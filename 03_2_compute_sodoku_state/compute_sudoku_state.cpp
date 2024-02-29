// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <string.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/************** begin assignment **************/
// Sudoku is a popular logic-based combinatorial number placement puzzle. The
// objective is to fill a 9 x 9 grid with digits subject to the constraint that
// each column, each row, and each of the nine 3 x 3 sub-grids that compose the
// grid contains unique integers.
// In case you need an introduction to Sudoku:
// https://www.learn-sudoku.com/sudoku-rules.html

// We define three different states in which a Sudoku board can be.
enum class state { invalid,
                   valid,
                   solved };
// invalid --> board violates the Sudoku rules
// valid --> board corresponds to the Sudoku rules
// solved --> the puzzle is solved

// Note that the only valid characters are "123456789" and the space ' ' meaning
// an empty field.
// Note that we do not care if a board can actually be solved, we only check if
// it violates the rules, or is valid, or is in a solved state.
// Of course a solved board is also valid, but we only return solved.

// TODO: implement a function that returns the state of a Sudoku board
state compute_sudoku_state(const string &board) {
    if (board.size() != 81) {
        return state::invalid;
    }

    bool solved = true;
    for (int row = 0; row < 9; row++) {
        unordered_set<char> check_row;
        for (int col = 0; col < 9; col++) {
            char currentChar = board[row * 9 + col];
            if (!isdigit(currentChar) && currentChar != ' ' || currentChar == '0') {
                return state::invalid;
            }
            if (currentChar != ' ' && check_row.find(currentChar) != check_row.end()) {
                return state::invalid;
            }
            if (currentChar == ' ' || currentChar < '1' || currentChar > '9') {
                solved = false;
            }
            check_row.insert(currentChar);
        }
    }

    for (int col = 0; col < 9; col++) {
        unordered_set<char> check_col;
        for (int row = 0; row < 9; row++) {
            char currentChar = board[col * 9 + row];
            if (!isdigit(currentChar) && currentChar != ' ') {
                return state::invalid;
            }
            if (currentChar != ' ' && check_col.find(currentChar) != check_col.end()) {
                return state::invalid;
            }
            check_col.insert(currentChar);
        }
    }

    vector<unordered_set<char>> check_subbox(9);
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int loc = (row / 3) * 3 + col / 3;
            char currentChar = board[row * 9 + col];
            if (!isdigit(currentChar) && currentChar != ' ') {
                return state::invalid;
            }
            if (currentChar != ' ' && check_subbox[loc].find(currentChar) != check_subbox[loc].end()) {
                return state::invalid;
            }
            check_subbox[loc].insert(currentChar);
        }
    }

    if (solved) {
        return state::solved;
    }

    return state::valid;
}

/*************** end assignment ***************/

int main() {
    {
        string board =
            "274935168"
            "198726435"
            "563814729"
            "356187294"
            "419562873"
            "782493516"
            "821349657"
            "947651382"
            "63527894";  // invalid size
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "274935168"
            "198726435"
            "563814729"
            "356187294"
            "419562873"
            "782493516"
            "821349657"
            "947651382"
            "6352789412";  // invalid size
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "   9  1 4"
            " 2  5 7  "
            "     25 6"
            "    194 5"
            " 6574391 "
            "4 1 26  8"
            " 18375 4 "
            " : 4  631"  // |:|
            " 4  6    ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "586937124"
            "129654783"
            "734182596"
            "372819465"
            "865743912"
            "491526308"  // |0|
            "618375249"
            "257498631"
            "943261857";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "586937124"
            "129654783"
            "734182596"
            "372819465"
            "865743912"
            "4915263a8"  // |a|
            "618375249"
            "257498631"
            "943261857";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "145673829"
            "389215674"
            "762948135"
            "296157483"
            "814369752"
            "573824961"
            "957436218"
            "628591347"
            "431782596";
        assert(compute_sudoku_state(board) == state::solved);
    }
    {
        string board =
            "495287163"
            "821369547"
            "367145298"
            "179854632"
            "634972815"
            "582613974"
            "216438759"
            "953721486"
            "748596321";
        assert(compute_sudoku_state(board) == state::solved);
    }
    {
        string board =
            "145673829"
            "381215674"  // 38|1|
            "762948135"
            "296157483"
            "814369752"
            "573824961"
            "957436218"
            "628591347"
            "431782596";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "145673829"
            "38 215674"
            "762948135"
            "296157483"
            "814369752"
            "573824961"
            "957436 18"
            "628591347"
            "431782596";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            " 4    897"
            " 379   52"
            "8 27  3  "
            "9  4 7  6"
            " 8  9  3 "
            "6 3 18 49"
            "  83 192 "
            "26   4  3"
            " 142596  ";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            " 4    897"
            " 379   52"
            "8 27  3  "
            "9  6 7  6"  // 9  |6|
            " 8  9  3 "
            "6 3 18 49"
            "  83 192 "
            "26   4  3"
            " 142596  ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            " 4    897"
            " 379   52"
            "8 27  3  "
            "9  4 7  6"
            " 8  9  3 "
            "6 3 18 49"
            "  83 193 "  //   83 19|3|
            "26   4  3"
            " 142596  ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "   9  1 4"
            " 2  5 7  "
            "     25 6"
            "    194 5"
            " 6574391 "
            "4 1 26  8"
            " 18375 4 "
            "   4  631"
            " 4  6    ";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "2  9  1 4"  // |2|
            " 2  5 7  "
            "     25 6"
            "    194 5"
            " 6574391 "
            "4 1 26  8"
            " 18375 4 "
            "   4  631"
            " 4  6    ";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "         "
            "         "
            "         "
            "         "
            "         "
            "         "
            "         "
            "         "
            "         ";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   4     "
            "    5    "
            "     6   "
            "      7  "
            "       8 "
            "        9";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::valid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "      1  "
            "      32 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1    7"
            "    2 7  "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "  4   1  "
            " 4     2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2 2     "
            "  3      "
            "   1     "
            "    2    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            "   1 6   "
            "   62    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    {
        string board =
            "1        "
            " 2       "
            "  3      "
            " 5 1     "
            "5   2    "
            "     3   "
            "      1  "
            "       2 "
            "        3";
        assert(compute_sudoku_state(board) == state::invalid);
    }
    cout << "all tests passed" << endl;
}
