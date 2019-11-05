/**
    standard: c++11
    visvalingam.cpp
    Purpose: visvalingam's algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <vector>

using namespace std;

/* Visvalingam algoritm returns a new vector with the points that match with the compression level */
template <typename Point>
extern vector<Point> visvalingam(const vector<Point> &data, const int compression_level);
