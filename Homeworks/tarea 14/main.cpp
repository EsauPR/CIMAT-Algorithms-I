#include <iostream>
#include <fstream>
#include "convex_hull.hpp"

using namespace std;


vector<Point> read_points(string file_name) {
    ifstream f_in(file_name);
    if (!f_in.is_open()) {
        cout << "Error opening: " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    int npoints;
    double x, y;
    vector<Point> points;

    f_in >> npoints;
    while (npoints--) {
        f_in >> x >> y;
        Point p(x, y);
        points.push_back(p);
    }

    return points;
}

int main(int argc, char * argv[]) {
    if (argc < 1) {
        cout << "Missingg arguments: [file name]" << endl;
        exit(EXIT_FAILURE);
    }

    vector<Point> points = read_points(argv[1]);
    // ConvexHull::_print(points);

    cout << "Jarvis's march";
    vector<Point> result_points = ConvexHull::jarvis_march(points, false);
    ConvexHull::_print(result_points);

    cout << "Graham's Scan";
    result_points = ConvexHull::andrew_monotone_chain(points, false);
    ConvexHull::_print(result_points);

    cout << "Andrew's Monotone Chain";
    result_points = ConvexHull::andrew_monotone_chain(points, false);
    ConvexHull::_print(result_points);

    return 0;
}
