
#include "cstdlib"
#include "ctime"

#define PERCEPTRON_IMPORT
#include "perceptron.hpp"

using namespace std;

Perceptron::Perceptron(int x_size) {
    _size = x_size;
    _weights.resize(x_size);

    for (int i = 0; i < x_size; i++) {
        _weights[i] = rand() % 1000;
    }
}

double Perceptron::threshold_function(vector<double> x) {
    double threshold = 0;
    for (int i = 0; i < _size; i++) {
        threshold += _weights[i] * x[i];
    }

    return threshold;
}
