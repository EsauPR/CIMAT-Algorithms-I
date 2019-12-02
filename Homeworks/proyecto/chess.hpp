/**
    C++, standard: c++11
    chess.coo
    Purpose: Prototype to solve n queen problem with k fixed queens

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef CHESS_H

#include <set>
#include <map>
#include <vector>

#ifdef CHESS_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

class Chess {
    private:
        vector<int> _board;
        vector<int> _solution;
        int _size = 0;
        int _nsols = 0;
        int _max_queens_placed = 0;
        set<int> _fixed_queens_cols;

        bool _is_under_attack(int col);
        void _solve(int col, int placed_queens);
        void _show_ascii_solution(vector<int> board);


    public:
        Chess(int size);
        bool place_queen(int row, int col);
        void solve();
        void show(int argc, char** argv);
};



#undef CHESS_IMPORT
#undef EXTERN
#endif
