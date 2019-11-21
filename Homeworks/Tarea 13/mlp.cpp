#include <vector>

#define MLP_IMPORT
#include "mlp.hpp"

using namespace std;

MLP::MLP(vector<unsigned int> layers_sizes, unsigned int x_size) {
    _size = layers_sizes.size();

    for (unsigned int i = 0; i < _size; i++) {
        Layer layer(layers_sizes[i], (i == 0)? x_size : layers_sizes[i-1]);
    }
}

void MLP::_propagation(vector<double> x) {
    for (unsigned int i = 0; i < _size; i++) {
        _layers[i].fit((i==0)? x : _layers[i-1].get_thresholds());
    }
}

void MLP::train(TRAINING_SET training_set) {
    for (unsigned int i = 0; i < training_set.size(); i++) {
        _propagation(training_set[i].first);
    }
}
