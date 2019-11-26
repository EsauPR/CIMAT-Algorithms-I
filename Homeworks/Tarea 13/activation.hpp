#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <vector>

#ifdef ACTIVATION_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

typedef int activation_function_t;

class Activation {
    private:
        Activation();
        static double _sigmoid_function(double value);
        static double _sigmoid_function_derivate(double value);

    public:
        static const enum {
            SIGMOID,
            SIGMOID_DERIVATE,
        } functions_t;
        static double activate(double value, activation_function_t f);
        static double activate_derivate(double value, activation_function_t f);
        static vector<double> activate(vector<double> values, activation_function_t f);
        static vector<double> activate_derivate(vector<double> values, activation_function_t f);
        static void get_info(activation_function_t f);
};

#undef ACTIVATION_IMPORT
#undef EXTERN
#endif
