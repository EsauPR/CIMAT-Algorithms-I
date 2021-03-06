#ifndef POINT_H
#define POINT_H

// includes

#ifdef POINT_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

class Point {
    private:
        double _x, _y;
    public:
        Point(double x=0, double y=0);

        double get_x();
        double get_y();
};

#undef POINT_IMPORT
#undef EXTERN
#endif
