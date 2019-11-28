// externs includes
#define DRAW_IMPORT
#include "draw.hpp"

using namespace std;

Draw::Draw(int width, int height) {
    _width = width;
    _height = height;
    _surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    _cr = cairo_create(_surface);
}

Draw::~Draw() {
    cairo_destroy(_cr);
    cairo_surface_destroy(_surface);
}

// code
void Draw::draw_points(vector<Point> points, vector<Point> hull, double scalling_factor, string file_ouput) {
    cairo_set_source_rgb(_cr, 0, 0, 0);

    cairo_rectangle(_cr, 0, 0, _width, _height);
    cairo_fill(_cr);


    cairo_set_line_width(_cr, 2);

    cairo_set_source_rgb(_cr, 0, 1, 1);
    for (uint i = 0; i < points.size(); i++) {
        cairo_arc(_cr, points[i].get_x()*scalling_factor, points[i].get_y()*scalling_factor, 3, 0, 2 * 3.1416);
        cairo_fill(_cr);
    }


    cairo_set_source_rgb(_cr, 1, 1, 1);
    for (uint i = 0; i < hull.size(); i++) {
        cairo_arc(_cr, hull[i].get_x()*scalling_factor, hull[i].get_y()*scalling_factor, 3, 0, 2 * 3.1416);
        cairo_fill(_cr);
    }

    Point last = hull[hull.size()-1];
    for (uint i = 0; i < hull.size(); i++) {
        cairo_move_to(_cr, last.get_x()*scalling_factor, last.get_y()*scalling_factor);
        cairo_line_to(_cr, hull[i].get_x()*scalling_factor, hull[i].get_y()*scalling_factor);
        last = hull[i];
    }

    cairo_stroke(_cr);
    cairo_surface_write_to_png(_surface, file_ouput.c_str());
}
