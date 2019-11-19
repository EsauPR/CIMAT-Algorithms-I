#include <iostream>
#include <cmath>
#include <algorithm>
#include "individual.hpp"
#include "population.hpp"

#define SELECTION_IMPORT
#include "selection.hpp"

using namespace std;

template <typename Ind>
double Selection::_get_repr(Ind ind, double from, double to) {
    double range = abs(from - to);
    long long int upper = pow(2, ind.get_size());
    double delta = range / upper;
    // cout << "delta " << delta << endl;
    double repr = 0.0;
    uint size = ind.get_size();

    for (uint i = 0; i < size; i++) {
        if (ind.get_at(i)) {
            repr += (1LL << i) ;
        }
    }

    // cout << "repr " << repr << endl;

    repr = repr * delta + from;

    // cout << "repr " << repr << endl;

    return repr;
}

template <typename Ind>
double Selection::_h1_function_cost(Ind ind) {
    double x = Selection::_get_repr(ind, -30, 30);
    return x * x + 13;
}


template <typename Ind>
double Selection::_h2_function_cost(Ind ind) {
    double x = Selection::_get_repr(ind, -4, 7);
    return x * x * sin(x);
}

template <typename Ind>
vector<pair<Ind, double>> Selection::select_kbest(vector<Ind> population, unsigned int f_cost_t, unsigned int kbest) {
    vector<pair<double, int>> ranking;

    for (uint i = 0; i < population.size(); i++) {
        if (f_cost_t == _H1) {
            ranking.push_back(make_pair(Selection::_h1_function_cost(population[i]), i));
        } else if(f_cost_t == _H2) {
            ranking.push_back(make_pair(Selection::_h2_function_cost(population[i]), i));
        }
    }

    sort(ranking.begin(), ranking.end());

    vector<pair<Ind, double>> best_ind;

    for (int i = 0; i < kbest && i < population.size(); i++) {
        best_ind.push_back(make_pair(population[ranking[i].second], ranking[i].first));
    }

    return best_ind;

}

template  vector<pair<Individual, double>> Selection::select_kbest(vector<Individual>, unsigned int, unsigned int);
template double Selection::_get_repr(Individual, double, double);
template double Selection::_h1_function_cost(Individual);
template double Selection::_h2_function_cost(Individual);
