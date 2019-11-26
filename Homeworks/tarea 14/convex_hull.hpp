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
        ConvexHull();

    public:
        ~ConvexHull();
        static double _cross(Point a, Point b, Point c);
        static double _distance(Point a, Point b);
        static void _print(vector<Point> points);

        static vector<Point> jarvis_march(vector<Point> points);
        static vector<Point> graham_scan(vector<Point> points);
        static vector<Point> andrew_monotone_chain(vector<Point> points);
};


#undef CONVEX_HULL_IMPORT
#undef EXTERN
#endif
