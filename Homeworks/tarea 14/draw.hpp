#ifndef DRAW_H
#define DRAW_H

#include <string>
#include <vector>
#include <cairo.h>
#include "point.hpp"

#ifdef DRAW_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

class Draw {
    private:
        int _width = 1366;
        int _height = 768;
        cairo_surface_t * _surface = NULL;
        cairo_t * _cr = NULL;

    public:
        Draw(int width, int height);
        void draw_points(vector<Point> points, string file_ouput);
};


#undef DRAW_IMPORT
#undef EXTERN
#endif
