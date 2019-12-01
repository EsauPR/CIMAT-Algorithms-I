#include <iostream>
#include "chess.hpp"

using namespace std;


int main(int argc, char * argv[]) {
    int board_size = 0;
    int n_fixed_queens = 0;

    cout << "Board size: ";
    cin >> board_size;

    Chess chess(board_size);

    cout << "Number of fixed queens: ";
    cin >> n_fixed_queens;

    int x, y;
    for (int i = 0; i < n_fixed_queens; i++) {
        cout << "Coordenates for queen " << i+1 << ": ";
        cin >> x >> y;
        chess.place_queen(x, y);
    }


    chess.solve();
    chess.show(argc, argv);

    return 0;
}
