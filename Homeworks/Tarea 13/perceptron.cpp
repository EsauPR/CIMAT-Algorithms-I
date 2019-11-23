
#include "cstdlib"
#include "ctime"

#define PERCEPTRON_IMPORT
#include "perceptron.hpp"

using namespace std;


Perceptron::Perceptron(unsigned int x_size) {
    _size = x_size;
    _weights.resize(x_size);
    _bias = rand() % 100;

    for (unsigned int i = 0; i < x_size; i++) {
        _weights[i] = rand() % 1000;
    }
}


double Perceptron::get_bias() {
    return _bias;
}


void Perceptron::set_bias(double bias) {
    _bias = bias;
}

double Perceptron::threshold_function(vector<double> x) {
    double threshold = 0;
    for (unsigned int i = 0; i < _size; i++) {
        threshold += _weights[i] * x[i];
    }

    return threshold + _bias;
}


double Perceptron::threshold_function(vector<double> x, vector<double> w) {
    double threshold = 0;
    for (unsigned int i = 0; i < x.size(); i++) {
        threshold += w[i] * x[i];
    }

    return threshold + _bias;
}


vector<double> Perceptron::get_weights() {
    return _weights;
}


void Perceptron::update_weight(double factor, unsigned int index) {
    _weights[index] += factor;
}
