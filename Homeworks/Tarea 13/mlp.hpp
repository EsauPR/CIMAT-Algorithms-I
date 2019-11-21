#ifndef MLP_H
#define MLP_H

#include <vector>

#include "layer.hpp"

using namespace std;

#ifdef MLP_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

#define SAMPLE vector<double>
#define TRAINING_SET vector<pair<SAMPLE, double>>

class MLP {
    private:
        unsigned int _size;
        vector<Layer> _layers;

        void _propagation(vector<double> x);

    public:
        MLP(vector<unsigned int> layers_sizes, unsigned int x_size);
        void train(TRAINING_SET training_set);
};


#undef MLP_IMPORT
#undef EXTERN
#endif
