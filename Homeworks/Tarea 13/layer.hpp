#ifndef LAYER_H
#define LAYER_H

#include <vector>

#include "perceptron.hpp"

#ifdef LAYER_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

class Layer {
    private:
        int _size;
        vector<Perceptron> _neurons;
        vector<double> _thresholds;

    public:
        Layer * _prev = NULL;
        Layer * _next = NULL;

        Layer(int layer_size, int n_weights);
        void fit(vector<double> x);
        vector<double> get_thresholds();
};

#undef LAYER_IMPORT
#undef EXTERN
#endif
