#include "canvas.hpp"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include <vector>

using namespace std;

int main(int argc, char** argv) {
    int n_quees = 10;
    int spacing_size = 60;
    static auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.resize(n_quees * spacing_size, n_quees * spacing_size);
    window.set_title("Chess N-Queens");

    vector<int> sol = {0, 3, 4, 2, 4 };

    CCanvas board(sol, spacing_size);
    window.add(board);
    board.show();

    return app->run(window);
}
