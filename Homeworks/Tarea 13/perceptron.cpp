
#include "cstdlib"
#include "ctime"

#define PERCEPTRON_IMPORT
#include "perceptron.hpp"

using namespace std;


Perceptron::Perceptron(unsigned int x_size) {
    _size = x_size;
    _weights.resize(x_size);
    _bias = (double)(rand() % 100) / 100.0;

    for (unsigned int i = 0; i < x_size; i++) {
        _weights[i] = (double)(rand() % 100) / 100.0;
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

void Perceptron::set_weight(double value, int index) {
    _weights[index] = value;
}
