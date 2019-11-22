#include <iostream>
#include <vector>

#define MODULE_IMPORT
#include "layer.hpp"

using namespace std;

Layer::Layer(int layer_size, int n_weights) {
    _size = layer_size;
    _thresholds.resize(_size);
    _output.resize(_size);

    for (unsigned int i = 0; i < _size; i++) {
        Perceptron p(n_weights);
        _neurons.push_back(p);
    }
}

void Layer::fit(vector<double> x,  activation_function_t f) {
    for (unsigned int i = 0; i < _size; i++) {
        _thresholds[i] = _neurons[i].threshold_function(x);
        _output[i] = Activation::activate(_thresholds[i], f);
    }
}

vector<double> Layer::get_thresholds(vector<double> x, vector<vector<double>> w) {
    vector<double> thresholds(_size);

    for (unsigned int i = 0; i < _size; i++) {
        thresholds[i] = Perceptron::threshold_function(x, w[i]);
    }

    return thresholds;
}

vector<double> Layer::get_thresholds() {
    return _thresholds;
}

vector<double> Layer::get_output() {
    return _output;
}


unsigned int Layer::get_size() {
    return _size;
}


vector<double> Layer::get_weights(unsigned int index) {
    return _neurons[index].get_weights();
}

void Layer::set_bias(double bias) {
    for (unsigned int i = 0; i < _size; i++) {
        _neurons[i].set_bias(bias);
    }
}
