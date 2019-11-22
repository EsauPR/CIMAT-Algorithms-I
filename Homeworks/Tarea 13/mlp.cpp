#include <ctime>
#include <iostream>
#include <vector>

#define MLP_IMPORT
#include "mlp.hpp"

using namespace std;


MLP::MLP(vector<unsigned int> layers_sizes, unsigned int x_size) {
    srand(0);
    _size = layers_sizes.size();
    _f_act = Activation::SIGMOID;
    _f_cost = F_Cost::ECM;

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


vector<double> MLP::_get_deltas_layer(double d_cost, vector<double> d_act) {
    vector<double> deltas(d_act.size());
    for (unsigned i = 0; i < d_act.size(); i++) {
        deltas[i] = d_cost * d_act[i];
    }
    return deltas;
}

void MLP::_back_propagation(vector<double> y) {
    vector<vector<double>> deltas;
    vector<vector<double>> last_Ws;

    for (unsigned int  i = _size - 1; i >= 0; i--) {
        Layer layer = _layers[i];
        // Compute deltas
        if (i == _size - 1) { // Last layer
            double cost_der = F_Cost::evaluate_derivate(layer.get_output(), y, _f_cost);
            vector<double> act_der = Activation::activate_derivate(layer.get_output(), _f_act);
            deltas.push_back(_get_deltas_layer(cost_der, act_der));
        } else {
            vector<double> thresholds = _layers[i+1].get_thresholds(deltas[deltas.size() - 1], last_Ws);
            vector<double> act_der = Activation::activate_derivate(layer.get_output(), _f_act);
            vector<double> deltas_layer;
            for (unsigned int i = 0; i < act_der.size(); i++){
                deltas_layer.push_back(thresholds[i]*act_der[i]);
            }
            deltas.push_back(deltas_layer);
        }

        last_Ws.clear();

        // Gradient descent
        for (unsigned int j = 0; j < layer.get_size(); j++) {
            // layer.set_bias();
        }

    }

}


void MLP::train(vector<SAMPLE> X, SAMPLE Y) {
    for (unsigned int i = 0; i < _size; i++) {
        _propagation(X[i]);
        _back_propagation(Y);
    }
}
