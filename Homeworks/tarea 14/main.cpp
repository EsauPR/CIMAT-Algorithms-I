#include <iostream>
#include <fstream>
#include <ctime>
#include "convex_hull.hpp"
#include "pgm.hpp"

using namespace std;

/* Return a vector of Points from a file */
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

/* Returns a vector from a binary image format pgm */
vector<Point> read_image(const char * file_name) {
    pgmImage img = read_pgmImage(file_name);

    vector<Point> points;

    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            if (img.content[i][j] != 0) {
                Point p(i, j);
                points.push_back(p);
            }
        }
    }

    return points;
}

/* Returns a ramdon points */
vector<Point> get_ramdom_points(uint n) {
    vector<Point> points;

    for (uint i = 0; i < n; i++) {
        Point p( 10 + random() % 300, 10 + random() % 300 );
        points.push_back(p);
    }

    return points;
}


int main(int argc, char * argv[]) {
    if (argc < 2) {
        cout << "Missingg arguments: [file name]" << endl;
        exit(EXIT_FAILURE);
    }

    vector<Point> points;

    string option = argv[1];
    if (option == "-p") {
        points = read_points(argv[2]);
    } else if (option == "-i") {
        points = read_image(argv[2]);
    } else if (option == "-r") {
        points = get_ramdom_points(atoi(argv[2]));
    } else {
        cout << "Invalid option: " << option << endl;
        return 0;
    }

    unsigned t_start, t_end;
    double time;

    cout << "Jarvis's march" << endl;
    t_start=clock();
    vector<Point> result_points = ConvexHull::jarvis_march(points, false);
    t_end = clock();
    time = (double(t_end - t_start) / CLOCKS_PER_SEC);
    cout << "Time: " << time << endl;
    ConvexHull::_print(result_points);

    cout << "Graham's Scan" << endl;
    t_start=clock();
    result_points = ConvexHull::graham_scan(points, false);
    t_end = clock();
    time = (double(t_end - t_start) / CLOCKS_PER_SEC);
    cout << "Time: " << time << endl;
    ConvexHull::_print(result_points);

    cout << "Andrew's Monotone Chain" << endl;
    t_start=clock();
    result_points = ConvexHull::andrew_monotone_chain(points, false);
    t_end = clock();
    time = (double(t_end - t_start) / CLOCKS_PER_SEC);
    cout << "Time: " << time << endl;
    ConvexHull::_print(result_points);

    ConvexHull::draw(points, result_points, 2.0);

    return 0;
}
