#ifndef MLP_H
#define MLP_H

#include <vector>

#include "layer.hpp"
#include "activation.hpp"
#include "f_cost.hpp"

using namespace std;

#ifdef MLP_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

#define SAMPLE vector<double>


class MLP {
    private:
        unsigned int _x_feact__size;
        unsigned int _size;
        vector<Layer> _layers;
        activation_function_t _f_act;
        cost_function_t _f_cost;
        double _learning_rate;
        vector<unsigned int> _layers_config;
        vector<double> _errors;


        vector<double> _propagation(vector<double> x);
        void _back_propagation(vector<double> x, vector<double> y);

    public:
        MLP(vector<unsigned int> layers_sizes, unsigned int x_size);
        MLP(string file_name);
        double train(vector<SAMPLE> X, vector<SAMPLE> Y);
        vector<vector<double>> predict(vector<SAMPLE> X);
        void set_config(activation_function_t f_act,
                        cost_function_t f_cost,
                        double learning_rate=0.5);
        vector<double> _get_deltas_layer(double d_cost, vector<double> d_act);
        void show_config();
        void export_errors(string file_name="errors.txt");
        void export_model(string file_name="model.txt");
};


#undef MLP_IMPORT
#undef EXTERN
#endif
