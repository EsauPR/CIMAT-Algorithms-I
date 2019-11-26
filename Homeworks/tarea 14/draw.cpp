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
void Draw::draw_points(vector<Point> points, string file_ouput) {
    cairo_set_source_rgb(_cr, 0, 0, 0);

    cairo_rectangle(_cr, 0, 0, _width, _height);
    cairo_fill(_cr);

    cairo_set_source_rgb(_cr, 0, 1, 1);
    cairo_set_line_width(_cr, 3);

    cairo_stroke(_cr);
    cairo_surface_write_to_png(_surface, file_ouput.c_str());
}
