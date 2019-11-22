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
        double _bias;

    public:
        Perceptron(int x_size);
        double threshold_function(vector<double> x);
        static double threshold_function(vector<double> x, vector<double> w);
        void set_bias(double bias);
        vector<double> get_weights();
};

#undef PERCEPTRON_IMPORT
#undef EXTERN
#endif
