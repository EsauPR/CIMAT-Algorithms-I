#include <ctime>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#define MLP_IMPORT
#include "mlp.hpp"

using namespace std;


MLP::MLP(vector<unsigned int> layers_sizes, unsigned int x_size) {
    // srand(time( NULL ));
    srand(0);
    _size = layers_sizes.size();
    _f_act = Activation::SIGMOID;
    _f_cost = F_Cost::ECM;
    _learning_rate = 0.01;
    _layers_config = layers_sizes;

    for (unsigned int i = 0; i < _size; i++) {
        Layer layer(layers_sizes[i], (i == 0)? x_size : layers_sizes[i-1]);
        _layers.push_back(layer);
    }
}


void MLP::set_config(activation_function_t f_act, cost_function_t f_cost, double learning_rate) {
    _f_act = f_act;
    _f_cost = f_cost;
    _learning_rate = learning_rate;
}


void MLP::_propagation(vector<double> x) {
    for (unsigned int i = 0; i < _size; i++) {
        _layers[i].fit((i==0)? x : _layers[i-1].get_output(), _f_act);
    }
}


void MLP::_back_propagation(vector<double> x, vector<double> y) {
    vector<vector<double>> deltas;
    vector<vector<double>> last_Weights;
    vector<double> last_deltas_l;

    double cost = F_Cost::evaluate(_layers[_layers.size() - 1].get_output(), y, _f_cost);
    cout << "Error: " << cost << endl;

    for (int i = _size - 1; i >= 0; i--) {
        // Compute deltas
        if (i == (int)_size - 1) { // Last layer
            double cost_der = F_Cost::evaluate_derivate(_layers[i].get_output(), y, _f_cost);
            vector<double> deltas_l = Activation::activate_derivate(_layers[i].get_output(), _f_act);
            for (unsigned int j = 0; j < deltas_l.size(); j++) {
                deltas_l[j] *= cost_der;
            }
            deltas.push_back(deltas_l);
            last_deltas_l = deltas_l;
        } else { // First and hidden layers
            vector<double> act_der = Activation::activate_derivate(_layers[i].get_output(), _f_act);
            vector<double> deltas_l(last_Weights[0].size(), 0.0);
            for (unsigned int k = 0; k < last_deltas_l.size(); k++) {
                for (unsigned int j = 0; j < last_Weights[k].size(); j++) {
                    deltas_l[j] += last_deltas_l[k]*last_Weights[k][j];
                }
            }
            for (unsigned int k = 0; k < deltas_l.size(); k++) {
                deltas_l[k] *= act_der[k];
            }
            deltas.push_back(deltas_l);
            last_deltas_l = deltas_l;
        }

        last_Weights = _layers[i].get_all_weights();

        // Gradient descent
        // Update bias
        double mean = accumulate(last_deltas_l.begin(), last_deltas_l.end(), 0.0) / last_deltas_l.size();
        for (unsigned int j = 0; j < _layers[i].get_size(); j++) {
            _layers[i].set_bias(_layers[i].get_bias(j) - mean * _learning_rate, j);
        }
        // Update weights
        vector<double> prev_act = (i==0)?  x : _layers[i-1].get_output();
        for (unsigned int  k = 0; k < last_deltas_l.size(); k++) {
            for (unsigned int j = 0; j < prev_act.size(); j++){
                _layers[i].update_weight(-last_deltas_l[k]*prev_act[j] * _learning_rate, k, j);
            }
        }
    }
}


void MLP::train(vector<SAMPLE> X, vector<SAMPLE> Y) {
    for (unsigned int i = 0; i < X.size(); i++) {
        _propagation(X[i]);
        _back_propagation(X[i], Y[i]);
    }
}

void MLP::get_config() {
    cout << "\nNetwork architecture:" << endl;
    Activation::get_info(_f_act);
    F_Cost::get_info(_f_cost);
    cout << "Learning rate: " << _learning_rate << endl;
    cout << "Layers: " << _layers_config.size() << endl;
    for (unsigned int i = 0; i < _layers_config.size(); i++) {
        cout << "Layer " << i+1 << ", No. Neurons: " << _layers_config[i] << endl;
    }
    cout << endl;
}
