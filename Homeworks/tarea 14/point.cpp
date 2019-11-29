#include <iostream>

#define POINT_IMPORT
#include "point.hpp"

using namespace std;

Point::Point(double x, double y) {
    _x = x;
    _y = y;
}

double Point::get_x() {
    return _x;
}

double Point::get_y() {
    return _y;
}
