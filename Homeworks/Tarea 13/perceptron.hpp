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
        unsigned int _size;
        vector<double> _weights;
        double _bias;

    public:
        Perceptron(unsigned int x_size);
        double threshold_function(vector<double> x);
        double threshold_function(vector<double> x, vector<double> w);
        double get_bias();
        void set_bias(double bias);
        vector<double> get_weights();
        void update_weight(double factor, unsigned int index);
};

#undef PERCEPTRON_IMPORT
#undef EXTERN
#endif
