#include <cmath>
#include <vector>

#define ACTIVATION_IMPORT
#include "activation.hpp"

using namespace std;


Activation::Activation() {}


double Activation::_sigmoid_function(double value) {
    return 1.0 / (1.0 + exp(-value));
}


double Activation::_sigmoid_function_derivate(double value) {
    double act_value = Activation::_sigmoid_function(value);
    return act_value *  (1.0 - act_value);
}


double Activation::activate(double value, activation_function_t f) {
    switch (f) {
        case SIGMOID:
            return _sigmoid_function(value);
        default:
            return 0;
    }
}


double Activation::activate_derivate(double value, activation_function_t f) {
    switch (f) {
        case SIGMOID:
            return _sigmoid_function_derivate(value);
        default:
            return 0;
    }
}

vector<double> Activation::activate(vector<double> values, activation_function_t f) {
    vector<double> acts(values.size());
    for (unsigned int i = 0; i < values.size(); i++) {
        acts[i] = Activation::activate(values[i], f);
    }
    return acts;
}

vector<double> Activation::activate_derivate(vector<double> values, activation_function_t f) {
    vector<double> acts(values.size());
    for (unsigned int i = 0; i < values.size(); i++) {
        acts[i] = Activation::activate_derivate(values[i], f);
    }
    return acts;
}
