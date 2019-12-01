/**
    C++, standard: c++11
    canvas.cpp
    Purpose: Canvas prototype for cheess board

    @author Esaú Peralta
    @email esau.opr@gmail.com

    @references: https://github.com/morgner/Cairo-Tutorial
*/

#ifndef CANVAS_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <vector>

#ifdef CANVAS_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

class CCanvas: public Gtk::DrawingArea {
    public:
        CCanvas(vector<int> solution, int spacing_size=25);
        virtual ~CCanvas() { };

    private:
        int _board_size;
        int _spacing_size;
        vector<int> _solution;

        void draw_board(const Cairo::RefPtr<Cairo::Context>& cr);
        void draw_queen(const Cairo::RefPtr<Cairo::Context>& cr, int i, int j);

    protected:
        // Override default signal handler
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};


#undef CANVAS_IMPORT
#undef EXTERN
#endif
