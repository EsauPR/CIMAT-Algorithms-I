#ifndef F_COST_H
#define F_COST_H

#include <vector>

#ifdef F_COST_IMPORT
   #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

typedef int cost_function_t;

class F_Cost {
    private:
        F_Cost();
        static double _ecm_function(vector<double>X, vector<double> Y);
        static double _ecm_function_derivate(vector<double>X, vector<double> Y);

    public:
        static const enum {
            ECM,
        } cost_f_t;
        static double evaluate(vector<double>X, vector<double> Y, cost_function_t f);
        static double evaluate_derivate(vector<double>X, vector<double> Y, cost_function_t f);
};


#undef F_COST_IMPORT
#undef EXTERN
#endif
