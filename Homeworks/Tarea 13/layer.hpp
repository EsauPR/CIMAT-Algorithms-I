#ifndef LAYER_H
#define LAYER_H

#include <vector>

#include "perceptron.hpp"
#include "activation.hpp"

#ifdef LAYER_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

class Layer {
    private:
        unsigned int _size;
        vector<Perceptron> _neurons;
        vector<double> _thresholds;
        vector<double> _output;

    public:
        Layer(int layer_size, int n_weights);
        void fit(vector<double> x, activation_function_t f);
        vector<double> get_thresholds();
        vector<double> get_thresholds(vector<double> x, vector<vector<double>> w);
        vector<double> get_output();
        vector<double> get_weights(unsigned int index);
        unsigned int get_size();
        void set_bias(double bias);
};

#undef LAYER_IMPORT
#undef EXTERN
#endif
