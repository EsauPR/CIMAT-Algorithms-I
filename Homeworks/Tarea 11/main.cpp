/**
    standard: c++11
    main.cpp
    Purpose: Tarea 11 - visvalingam algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cairo.h>

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
vector<Point> visvalingam(const vector<Point> &data, const double compression_level) {
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

/* Return a vector of points that represents a figure */
vector<pair<double, double>> read_data(const string file_name) {
    ifstream file(file_name);

    if (file.fail()) {
        perror(file_name.c_str());
        exit(EXIT_FAILURE);
    }

    vector<pair<double, double>> data;
    string points_str;
    string x_str, y_str;

    while(file >> points_str) {
        stringstream stst(points_str);
        getline(stst, x_str, ',');
        getline(stst, y_str);
        data.push_back(make_pair(stod(x_str), stod(y_str)));
    }

    file.close();

    return data;
}

/* Save a set of points as an image */
void save_img(vector<pair<double, double>> data, string file_name) {
    int width = 1366, height = 768;
    cairo_surface_t * surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 0, 0, 0);

    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0, 1, 1);
    cairo_set_line_width(cr, 3);

    double min_x, max_x, min_y, max_y;
    min_x = max_x = -data[0].first;
    min_y = max_y = data[0].second;

    for (uint i = 0; i < data.size(); i++) {
        min_x = min(min_x, -data[i].first);
        max_x = max(max_x, -data[i].first);
        min_y = min(min_y, data[i].second);
        max_y = max(max_y, data[i].second);
    }

    int last_x = (-data[0].first - min_x) * width / (max_x - min_x);
    int last_y = (data[0].second - min_y) * height / (max_y - min_y);
    for (uint i = 1; i <= data.size(); i++) {
        int x = (-data[i % data.size()].first - min_x) * width / (max_x - min_x);
        int y = (data[i % data.size()].second - min_y) * height / (max_y - min_y);
        cairo_move_to(cr, width - last_x, height - last_y);
        cairo_line_to(cr, width - x, height - y);
        last_x = x;
        last_y = y;

    }

    cairo_stroke(cr);
    cairo_surface_write_to_png(surface, file_name.c_str());

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

/* Compute the Jaccard Index */
double jaccard_index(vector<pair<double, double>> data, vector<pair<double, double>> reduced) {
    map<pair<double, double>, int> frecs;

    for (uint i = 0; i < data.size(); i++) {
        frecs[data[i]] ++;
        if(i<reduced.size()) {
            frecs[reduced[i]] ++;
        }
    }

    map<pair<double, double>, int>::iterator it;

    uint two=0, one=0;
    for (it = frecs.begin(); it != frecs.end(); it++) {
        if (it->second == 1) {
            one++;
        } else {
            two++;
        }
    }

    return double(two) / (two+one);
}


int main(const int argc, const char * argv[]) {
    if (argc < 3) {
        cout << "Missing args value" << endl;
        return EXIT_FAILURE;
    }


    int compresion_level = max(1,  min(99, atoi(argv[2])));
    vector<pair<double, double>> data = read_data(argv[1]);

    cout << "Number of original points: " << data.size() << endl;
    string oname = "oaxaca_original.png";
    cout << "Writing original image to: " << oname << endl;
    save_img(data, "oaxaca_original.png");


    vector<pair<double, double>> result = visvalingam(data, compresion_level);
    cout << "Number of points after the compression: " << result.size() << endl;
    cout << "Compresion of: " << compresion_level << "%" << endl;
    cout << "Jaccard index: " << jaccard_index(data, result) << endl;
    string cname = "oaxaca_reduced.png";
    cout << "Writing compressed image to: " << cname << endl;
    save_img(result, cname);

    return EXIT_SUCCESS;
}
