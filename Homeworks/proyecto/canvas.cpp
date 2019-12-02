/**
    C++, standard: c++11
    canvas.cpp
    Purpose: Canvas for cheess board

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

// Includes

#define CANVAS_IMPORT
#include "canvas.hpp"

using namespace std;


CCanvas::CCanvas(vector<int> solution, int spacing_size) {
    _board_size = solution.size();
    _spacing_size = spacing_size;
    _solution = solution;
}


/* Draw a queen in any cell position */
void CCanvas::draw_queen(const Cairo::RefPtr<Cairo::Context>& cr, int i, int j) {
    double offset = _spacing_size / 5.0;
    double side = offset * 3;

    i *= _spacing_size;
    j *= _spacing_size;

    cr->set_line_width(2.0);
    cr->set_source_rgb(0.0, 0.0, 0.0);

    cr->move_to(j + offset, i + offset + side / 3.0);
    cr->line_to( j + offset, i + offset + side);

    cr->move_to(j + offset, i + offset + side);
    cr->line_to(j + offset + side, i + offset + side);

    cr->move_to(j + offset + side, i + offset + side);
    cr->line_to(j + offset + side, i + offset + side / 3.0);

    cr->move_to(j + offset + side, i + offset + side / 3.0);
    cr->line_to(j + offset + side / 3.0 * 2.0, i + offset + side / 3.0 * 2);

    cr->move_to(j + offset + side / 3.0 * 2.0, i + offset + side / 3.0 * 2);
    cr->line_to(j + offset + side / 4.0 * 2.0, i + offset );

    cr->move_to(j + offset + side / 4.0 * 2.0, i + offset );
    cr->line_to(j + offset + side / 3.0, i + offset + side / 3.0 * 2);

    cr->move_to(j + offset + side / 3.0, i + offset + side / 3.0 * 2);
    cr->line_to(j + offset, i + offset + side / 3.0);

    cr->stroke();
}


/* Draw the board */
void CCanvas::draw_board(Cairo::RefPtr<Cairo::Context> const & cr) {
    cr->set_line_width(0.5);

    for (int i = 0; i < _board_size; i++) {
        for (int j = 0; j < _board_size; j++) {
            if ((i % 2) ^ (j % 2)) {
                cr->set_source_rgb(1.0, 0.5, 0.0);
            } else {
                continue;
            }

            cr->rectangle(i*_spacing_size , j*_spacing_size , _spacing_size, _spacing_size);
            cr->fill();
            cr->stroke();
        }
    }
}


/* Draw a board and queens for any solution*/
bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr) {
    draw_board(cr);
    for (int i = 0; i < _board_size; i++) {
        draw_queen(cr, _solution[i], i);
    }

    return true;
}
