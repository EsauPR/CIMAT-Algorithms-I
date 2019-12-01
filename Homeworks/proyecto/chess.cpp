/**
    C++, standard: c++11
    chess.coo
    Purpose: Implementation to solve n queen problem with k fixed queens

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "canvas.hpp"

#define CHESS_IMPORT
#include "chess.hpp"

using namespace std;


Chess::Chess(int size) {
    _size = size;
    _board.resize(_size, -2);

}

void Chess::place_queen(int row, int col) {
    if (row >= _size || col >= _size) {
        cout << "Invalid Position" << endl;
        return;
    }
    // Working by cols
    _board[col] = row;
    _fixed_queens_cols.insert(col);
    _fixed_positions[col] = row;
}


void Chess::_show_ascii_solution(vector<int> board) {
    cout << "Sol: " << ++_nsols << endl;
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (board[j] == i) {
                cout << " Q ";
            } else {
                cout << " - ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


void Chess::show(int argc, char** argv) {
    _show_ascii_solution(_solution);
    cout << "Maximun number of queens placed: " << _max_queens_placed << endl;

    int n_quees = _size;
    int spacing_size = 60;
    static auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.resize(n_quees * spacing_size, n_quees * spacing_size);
    window.set_title("Chess N-Queens");

    CCanvas board(_solution, spacing_size);
    window.add(board);
    board.show();

    app->run(window);
}


bool Chess::_is_under_attack(int col) {
    if (_board[col] == -1) return false; // No queen placed
    // Check from col 0 until current col
    for (int i = 0; i < col ; i++) {
        if (_board[i] == -1) continue; // No queen placed
        // Same row or in diagonal
        if (_board[col] == _board[i] || col - i == abs(_board[i] - _board[col])) {
            return true;
        }
    }
    // Verify for fixed queens in an specifiq cols
    for (map<int, int>::iterator it = _fixed_positions.begin(); it != _fixed_positions.end(); it++) {
        // Same row or in diagonal
        if (_board[col] == it->second || abs(col - it->first) == abs(_board[col] - it->second)) {
            return true;
        }
    }

    return false;
}


void Chess::_solve(int col) {
    // Last col reached
    if (col == _size) {
        // _show_ascii_solution(_board);
        if (_max_queens_placed < _queens_placed) {
            _solution = _board;
            _max_queens_placed = _queens_placed;
        }
        return;
    }
    // Jump fixed queen
    if (_fixed_queens_cols.count(col)) {
        _solve(col + 1);
        return;
    }
    // Try to put a queen in any row for this col
    for (int row = -1; row < _size; row++) {
        if (row != -1) {
            _queens_placed ++;
        }
        _board[col] = row;
        if (!_is_under_attack(col)) {
            _solve(col + 1);
        }
        if (row != -1) {
            _queens_placed --;
        }
    }
}


void Chess::solve() {
    _nsols = 0;
    _max_queens_placed = 0;
    _queens_placed = _fixed_queens_cols.size();
    _solve(0);
}
