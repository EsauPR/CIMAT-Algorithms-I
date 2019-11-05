#include <iostream>
#include <cairo.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cairo_surface_t * surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 500, 200);
    cairo_t * cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_rectangle(cr, 20, 20, 120, 80);
    cairo_fill(cr);

    cairo_surface_write_to_png(surface, "img.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}
