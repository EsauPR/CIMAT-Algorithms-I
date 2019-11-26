#include <iostream>
#include <algorithm>
#include <set>

#define CONVEX_HULL_IMPORT
#include "convex_hull.hpp"

using namespace std;

void ConvexHull::_print(vector<Point> points) {
    cout << endl << points.size() << endl;
    for (uint i = 0; i < points.size(); i++) {
        cout << points[i].get_x() << " " << points[i].get_y() << endl;
    }
    cout << endl;
}


/* Returns the value for make the crooss product for vectors ab ac */
double ConvexHull::_cross(Point a, Point b, Point c) {
    return (a.get_y() - c.get_y()) * (a.get_x() - b.get_x()) - (a.get_y() - b.get_y()) * (a.get_x() - c.get_x());
}

/* Returns the distance between to points whitout make the sqrt operation */
double ConvexHull::_distance(Point a, Point b) {
    return (a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) + (a.get_y() - b.get_y()) * (a.get_y() - b.get_y());
}


vector<Point> ConvexHull::jarvis_march(vector<Point> points) {
    // Get the leftmost point
    uint start = 0;
    for (uint i = 1; i < points.size(); i++) {
        if (points[i].get_x() < points[start].get_x()) {
            start = i;
        }
    }

    uint current = start;
    set<uint> _result; // To avoid collisions
    vector<uint> result;

    _result.insert(start);
    result.push_back(start);

    vector<uint> collinear_points;

    while(true) {
        uint next_target = 0;
        for (uint i = 1; i < points.size(); i++) {
            if (i == current) continue;
            double cross_value = ConvexHull::_cross(points[current], points[next_target], points[i]);
            // if val > 0 it means points[i] is on left of current -> next_target. Make him the next_target.
            if (cross_value > 0) {
                next_target = i;
                //reset collinear points because we now have a new next_target.
                collinear_points.clear();
            } else if (cross_value == 0) { //if cross_value is 0 then collinear current, next_target and points[i] are collinear.
                //if its collinear point then pick the further one but add closer one to list of collinear points.
                if (_distance(points[current], points[next_target]) - _distance(points[current], points[i]) < 0) {
                    collinear_points.push_back(next_target);
                    next_target = i;
                } else { //just add points[i] to collinear_points list. If next_target indeed is the next point on
                    //convex then all points in collinear points will be also on boundary.
                    collinear_points.push_back(i);
                }
            }
            //else if cross_value < 0 then nothing to do since points[i] is on right side of current -> next_target.
        }
        //add all points in collinear_points to result.
        for (uint i = 0; i < collinear_points.size(); i++) {
            if (!_result.count(collinear_points[i])) {
                _result.insert(collinear_points[i]);
                result.push_back(collinear_points[i]);
            }
        }
        //if next_target is same as start it means we have formed an envelope and its done.
        if (next_target == start) {
            break;
        }
        //add next_target to result and set current to next_target.
        if (!_result.count(next_target)) {
            _result.insert(next_target);
            result.push_back(next_target);
        }
        current = next_target;
    }

    vector<Point> result_points;
    for (uint i = 0; i < result.size(); i++) {
        result_points.push_back(points[result[i]]);
    }

    return result_points;
}
