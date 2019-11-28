#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include "point.hpp"

#ifdef CONVEX_HULL_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;


class ConvexHull {
    private:
        static Point _pivot;

        ConvexHull();
        static double _cross(Point a, Point b, Point c);
        static double _distance(Point a, Point b);
        static bool _compare(Point a, Point b);
        static bool _compare_angle(Point a, Point b);

    public:
        ~ConvexHull();
        static void _print(vector<Point> points);
        static void draw(vector<Point> points, vector<Point> hull, double scalling_factor=1.0);

        static vector<Point> jarvis_march(vector<Point> points, bool collinears=true);
        static vector<Point> graham_scan(vector<Point> points, bool collinears=true);
        static vector<Point> andrew_monotone_chain(vector<Point> points, bool collinears=true);
};


#undef CONVEX_HULL_IMPORT
#undef EXTERN
#endif
