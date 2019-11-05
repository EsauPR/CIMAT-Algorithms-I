/**
    standard: c++11
    visvalingam.cpp
    Purpose: visvalingam's algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/* Triangle struct */
typedef struct s_triangle {
    int index[3];
    double area;
    struct s_triangle * next;
    struct s_triangle * prev;
} Triangle;


/* Return a aproximation for the triangle area (do not divide by 2)*/
template<typename Point>
static double compute_area(Point p1, Point p2, Point p3) {
    return abs((p1.first-p3.first) * (p2.second-p3.second) - (p1.second-p3.second) * (p2.first-p3.first));
}

/* Funtion to sort the triangles */
static bool compare( const Triangle a, const Triangle b){
    if (a.area != b.area) return a.area < b.area;
    return false;
}

/* Visvalingam algoritm returns a new vector with the points that match with the compression level */
template <typename Point>
vector<Point> visvalingam(const vector<Point> &data, const int compression_level) {
    vector<int> removed(data.size(), -1);

    vector<Triangle> triangles;

    for (uint i = 1; i < data.size() - 1; i++) {
        Triangle t;
        t.index[0] = i-1;
        t.index[1] = i;
        t.index[2] = i + 1;
        t.area = -compute_area(data[i-1], data[i], data[i+1]);
        t.next = NULL;
        t.prev = NULL;
        triangles.push_back(t);
    }

    for (uint i = 0; i < triangles.size(); i++){
        if (i > 0) {
            triangles[i].prev = &(triangles[i-1]);
        }
        if (i < triangles.size() - 1) {
            triangles[i].next = &(triangles[i+1]);
        }
    }

    // double max_area = 0.0;
    for (uint i = 0; i < triangles.size(); i++) {
        sort(&(triangles[i]), &(triangles[triangles.size()-1]), compare);
        Triangle t = triangles[i];
        removed[t.index[1]] = data.size() - i;

        if (t.next) {
            t.prev->next = t.next;
            t.prev->index[2] = t.index[2];
            t.prev->area = -compute_area(data[t.prev->index[0]], data[t.prev->index[2]], data[t.prev->index[2]]);
        }

        if (t.next) {
            t.next->prev = t.prev;
            t.next->index[0] = t.index[0];
            t.next->area = compute_area(data[t.next->index[0]], data[t.next->index[1]], data[t.next->index[2]]);
        }
    }


    uint nignore = triangles.size() * compression_level / 100.0;

    vector <bool> ignore(data.size(), true);
    for (uint i = 0; i < nignore; i++) {
        ignore[triangles[i].index[1]] = false;
    }

    vector<Point> result;
    for (uint i = 0; i < data.size(); i++) {
        if (ignore[i]) {
            result.push_back(data[i]);
        }
    }

    return result;
}
