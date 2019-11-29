#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include "draw.hpp"

#define CONVEX_HULL_IMPORT
#include "convex_hull.hpp"

using namespace std;

/* Init pivot */
Point ConvexHull::_pivot = Point(0 ,0);


/* Print a vector */
void ConvexHull::_print(vector<Point> points) {
    cout << endl << points.size() << endl;
    for (uint i = 0; i < points.size(); i++) {
        cout << points[i].get_x() << " " << points[i].get_y() << endl;
    }
    cout << endl;
}


/* Returns the value for make the crooss product for vectors ab ac */
double ConvexHull::_cross(Point a, Point b, Point c) {
    return (b.get_x() - a.get_x()) * (c.get_y() - a.get_y()) - (b.get_y() - a.get_y()) * (c.get_x() - a.get_x());
}


/* Returns the distance between to points whitout make the sqrt operation */
double ConvexHull::_distance(Point a, Point b) {
    return (a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) + (a.get_y() - b.get_y()) * (a.get_y() - b.get_y());
}


/* Returns true if 'a' is the lowest and lefmost */
bool ConvexHull::_compare(Point a, Point b) {
    return a.get_y() < b.get_y() || (a.get_y() == b.get_y() && a.get_x() < b.get_x());
}


/* Compara the angle for two points by the lowest angle*/
bool ConvexHull::_compare_angle(Point a, Point b) {
    if (_cross(_pivot, a, b) == 0.0) {
        if (_pivot.get_x() < a.get_x()) {
            // The closer point must be first
            return _distance(_pivot, a) < _distance(_pivot, b);
        } else {
            // The farthest point must be first
            return _distance(_pivot, a) > _distance(_pivot, b);
        }
    }

    double delta_1x = a.get_x() - _pivot.get_x();
    double delta_1y = a.get_y() - _pivot.get_y();
    double delta_2x = b.get_x() - _pivot.get_x();
    double delta_2y = b.get_y() - _pivot.get_y();

    return (atan2(delta_1y, delta_1x) - atan2(delta_2y, delta_2x)) < 0;
}


/* Jarvis;s March Algorithm */
vector<Point> ConvexHull::jarvis_march(vector<Point> points, bool collinears) {
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
            double cross_value = _cross(points[current], points[next_target], points[i]);
            if (cross_value > 0) { // points[i] is on left of current
                next_target = i; // Take as new target point
                collinear_points.clear();
            } else if (cross_value == 0) { // points[i] is collinear
                // Inserte the point that is on the middle
                if (_distance(points[current], points[next_target]) - _distance(points[current], points[i]) < 0) {
                    collinear_points.push_back(next_target);
                    next_target = i;
                } else {
                    collinear_points.push_back(i);
                }
            }
        }

        if (collinears) { // Add the collinears points
            for (uint i = 0; i < collinear_points.size(); i++) {
                if (!_result.count(collinear_points[i])) {
                    _result.insert(collinear_points[i]);
                    result.push_back(collinear_points[i]);
                }
            }
        }

        if (next_target == start) { // Come back to the start
            break;
        }

        if (!_result.count(next_target)) {
            _result.insert(next_target);
            result.push_back(next_target);
        }

        current = next_target;
    }

    // Return a vector with the points
    vector<Point> hull;
    for (uint i = 0; i < result.size(); i++) {
        hull.push_back(points[result[i]]);
    }

    return hull;
}


/* Graham Scan's Algorithm */
vector<Point> ConvexHull::graham_scan(vector<Point> points, bool collinears) {
    uint size = points.size();
    // Get the point whit lowest Y and rigthmost X
    uint start = 0;
    for (uint i = 1; i < size; i++) {
        if (_compare(points[i], points[start])) {
            start = i;
        }
    }
    // Set pivot and set points[0] to points[start]
    _pivot = points[start];
    points[start] = points[0];
    points[0] = _pivot;
    // Sort the points around the pivot
    sort(++points.begin(), points.end(), _compare_angle);
    // ConvexHull::_print(points);

    vector<Point> hull;

    // Set the 3 first points
    hull.push_back(points[size-1]);
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (uint i = 2; i <= size; ) {
        uint j = hull.size() - 1;
        double cross = _cross(hull[j-1], hull[j], points[i % size]);
        if (collinears && cross >= 0) {
            hull.push_back(points[i%size]);
            i++;
        } else if (!collinears && cross > 0) {
            hull.push_back(points[i%size]);
            i++;
        } else {
            hull.pop_back();
        }
    }

    hull.erase(hull.begin());
    hull.pop_back();

    return hull;
}


/* Andrw's Monotone Algorithm */
vector<Point> ConvexHull::andrew_monotone_chain(vector<Point> points, bool collinears) {
    sort(points.begin(),points.end(), ConvexHull::_compare);
	int n = points.size(), k=0;

    vector<Point> hull(2 * n);

    // Build the upper side
	for(int i=0; i<n; i++) {
        if (collinears) {
            while(k >= 2 && _cross(hull[k-2], hull[k-1], points[i]) < 0) {
                k--;
            }
        } else {
            while(k >= 2 && _cross(hull[k-2], hull[k-1], points[i]) <= 0) {
                k--;
            }
        }
		hull[k++] = points[i];
	}
    // Build the lower side
    for(int i=n-2, t=k+1;i>=0; i--) {
        if (collinears) {
            while(k>=t && _cross(hull[k-2], hull[k-1], points[i]) < 0) {
                k--;
            }
        } else {
            while(k>=t && _cross(hull[k-2], hull[k-1], points[i]) <= 0) {
                k--;
            }
        }
		hull[k++] = points[i];
	}

    hull.resize(k-1);

    return hull;
}


void ConvexHull::draw(vector<Point> points, vector<Point> hull, double scalling_factor, string file_name) {
    Draw draw(1024, 768);
    draw.draw_points(points, hull, scalling_factor, file_name);
}
