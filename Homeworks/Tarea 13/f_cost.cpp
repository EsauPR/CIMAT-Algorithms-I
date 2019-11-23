#include <cmath>

#define F_COST_IMPORT
#include "f_cost.hpp"

using namespace std;


double F_Cost::_ecm_function(vector<double>y_est, vector<double> y_real) {
    double cost = 0.0;

    for (unsigned int i = 0; i < y_est.size(); i++) {
        cost += (y_est[i] - y_real[i]) * (y_est[i] - y_real[i]);
    }

    return cost;
}


double F_Cost::_ecm_function_derivate(vector<double>y_est, vector<double> y_real) {
    double cost = 0.0;

    for (unsigned int i = 0; i < y_est.size(); i++) {
        cost += (y_est[i] - y_real[i]);
    }

    return cost;
}


double F_Cost::evaluate(vector<double>y_est, vector<double> y_real, cost_function_t f) {
    switch (f) {
        case ECM:
            return F_Cost::_ecm_function(y_est, y_real);
        default:
            return 0;
    }
}


double F_Cost::evaluate_derivate(vector<double>y_est, vector<double> y_real, cost_function_t f) {
    switch (f) {
        case ECM:
            return F_Cost::_ecm_function_derivate(y_est, y_real);
        default:
            return 0;
    }
}
