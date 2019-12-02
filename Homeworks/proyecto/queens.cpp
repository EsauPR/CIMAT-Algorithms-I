#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>

using namespace std;


int nsols = 0;
map<int, int> fixed_positions;
set<int> fixed_queens;

int queens_placed = 0;
int max_queens_placed = 0;


void print_sol(int n_queens, vector<int> & sol) {
    cout << "Sol: " << ++nsols << endl;
    for (int i = 0; i < n_queens; i++) {
        for (int j = 0; j < n_queens; j++) {
            if (sol[j] == i) {
                cout << " Q ";
            } else {
                cout << " - ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


bool is_valid(int col, vector<int> & board) {
    if (board[col] == -1) {
        return true; // No queen
    }


    for (int i = 0; i < col ; i++) {
        if (board[i] == -1) continue; // No queen
        // Same row or in diagonal
        if (board[col] == board[i] || col - i == abs(board[i] - board[col])) {
            return false;
        }
    }

    for (map<int, int>::iterator it = fixed_positions.begin(); it != fixed_positions.end(); it++) {
        // Same row or in diagonal
        if (board[col] == it->second || abs(col - it->first) == abs(board[col] - it->second)) {
            return false;
        }
    }

    return true;
}


void solve(int n_queens, int col, vector<int> & board) {
    if (col == n_queens) {
        print_sol(n_queens, board);
        max_queens_placed = max(max_queens_placed, queens_placed);
        return;
    }

    if (fixed_queens.count(col)) {
        solve(n_queens, col+1, board);
        return;
    }

    for (int i = -1; i < n_queens; i++) {
        if (i != -1) {
            queens_placed ++;
        }

        board[col] = i;
        if (is_valid(col, board)) {
            solve(n_queens, col+1, board);
        }

        if (i != -1) {
            queens_placed --;
        }
    }
}


int main() {
    const int size = 8;
    vector<int> board(size, -2);

    board[1] = 1;
    fixed_positions[1] = 1;
    fixed_queens.insert(1);

    board[7] = 4;
    fixed_positions[7] = 4;
    fixed_queens.insert(7);

    queens_placed = fixed_queens.size();
    solve(size, 0, board);

    cout << "Max queens: " << max_queens_placed  << endl;

    return 0;
}
