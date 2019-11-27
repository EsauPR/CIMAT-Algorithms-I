#include <iostream>
#include <algorithm>
#include <set>

#define CONVEX_HULL_IMPORT
#include "convex_hull.hpp"

using namespace std;

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
    // return (a.get_y() - c.get_y()) * (a.get_x() - b.get_x()) - (a.get_y() - b.get_y()) * (a.get_x() - c.get_x());
    return (b.get_x() - a.get_x()) * (c.get_y() - a.get_y()) - (b.get_y() - a.get_y()) * (c.get_x() - a.get_x());
}


/* Returns the distance between to points whitout make the sqrt operation */
double ConvexHull::_distance(Point a, Point b) {
    return (a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) + (a.get_y() - b.get_y()) * (a.get_y() - b.get_y());
}


/* compare function between two points downmost and lefmost */
bool ConvexHull::_compare(Point a, Point b) {
    return a.get_y() < b.get_y() || (a.get_y() == b.get_y() && a.get_x() < b.get_x());
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
            double cross_value = ConvexHull::_cross(points[current], points[next_target], points[i]);
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
    vector<Point> result_points;
    for (uint i = 0; i < result.size(); i++) {
        result_points.push_back(points[result[i]]);
    }

    return result_points;
}


/* Graham Scan's Algorithm */
vector<Point> ConvexHull::graham_scan(vector<Point> points, bool collinears) {

}


/* Andrw's Monotone Algorithm */
vector<Point> ConvexHull::andrew_monotone_chain(vector<Point> points, bool collinears) {
    sort(points.begin(),points.end(), ConvexHull::_compare);
	int n = points.size(), k=0;

    vector<Point> result(2 * n);

    // Build the upper side
	for(int i=0; i<n; i++) {
        if (collinears) {
            while(k >= 2 && ConvexHull::_cross(result[k-2], result[k-1], points[i]) < 0) {
                k--;
            }
        } else {
            while(k >= 2 && ConvexHull::_cross(result[k-2], result[k-1], points[i]) <= 0) {
                k--;
            }
        }
		result[k++] = points[i];
	}
    // Build the lower side
    for(int i=n-2, t=k+1;i>=0; i--) {
        if (collinears) {
            while(k>=t && ConvexHull::_cross(result[k-2], result[k-1], points[i]) < 0) {
                k--;
            }
        } else {
            while(k>=t && ConvexHull::_cross(result[k-2], result[k-1], points[i]) <= 0) {
                k--;
            }
        }
		result[k++] = points[i];
	}

    result.resize(k-1);

    return result;
}
