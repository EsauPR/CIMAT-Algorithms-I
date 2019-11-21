#include <vector>

#define MODULE_IMPORT
#include "layer.hpp"

using namespace std;

Layer::Layer(int layer_size, int n_weights) {
    _size = layer_size;

    for (int i = 0; i < _size; i++) {
        Perceptron p(n_weights);
        _neurons.push_back(p);
    }
}

void Layer::fit(vector<double> x) {
    for (int i = 0; i < _size; i++) {
        _thresholds[i] = _neurons[i].threshold_function(x);
    }
}

vector<double> Layer::get_thresholds() {
    return _thresholds;
}
