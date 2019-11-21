#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>

#ifdef PERCEPTRON_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

class Perceptron {
    private:
        int _size;
        vector<double> _weights;

    public:
        Perceptron(int x_size);
        double threshold_function(vector<double> x);
};

#undef PERCEPTRON_IMPORT
#undef EXTERN
#endif
