
#include "selection.hpp"

using namespace std;

template <typename Ind>
double Selection::_h1_function_cost(Ind ind, double from=0.5, double to=10) {
    double delta = (to - from) / ind.size();

    return 1.0;
}

template <typename Ind>
double Selection::_h2_function_cost(Ind ind, double from=0.5, double to=10) {
    return 1.0;
}

template <typename Ind>
void Selection::select_best(vector<Ind> population,int f_cost_t) {
    vector<pair<double, int>> ranking;

    for (uint i = 0; i < population.size(); i++) {
        if (f_cost_t == _H1) {
            ranking.push_back(make_pair(_h1_function_cost(population[i]), i));
        }
    }
}
