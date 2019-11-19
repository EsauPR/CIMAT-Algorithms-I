#include <iostream>
#include <cstdlib>
#include <ctime>
#include "individual.hpp"

#define UMDA_IMPORT
#include "umda.hpp"

using namespace std;

template <class Ind>
UMDA<Ind>::UMDA(Population<Ind> population) {
    _population_zero = population;
}

template <class Ind>
vector<int> UMDA<Ind>::_get_frequencies() {
    vector<int> frecs(_population.get_at(0).get_size());

    for (uint i = 0; i < _population.get_size(); i++) {
        Ind ind = _population.get_at(i);
        for (int j = 0; j < ind.get_size(); j++) {
            if (ind.get_at(j)) {
                frecs[j] ++;
            }
        }
    }

    return frecs;
}

template<class Ind>
vector<bool> UMDA<Ind>::generate_genome(vector<int> frecs) {
    vector<bool> genome(frecs.size(), false);

    for (unsigned int i = 0; i < frecs.size(); i++) {
        if( frecs[i] <= rand() % 100) {
            genome[i] = true;
        }
    }

    return genome;
}

template<class Ind>
void UMDA<Ind>::run(unsigned int f_cost_t, unsigned int kbest, unsigned int max_iters) {
    _population = _population_zero;

    while (max_iters--){
        vector<int> frecs = _get_frequencies();
        vector<pair<Ind, double>> best_inds = Selection::select_kbest(_population.get_individuals(), f_cost_t, kbest);

        _best_ind = best_inds[0].first;
        _best_rank = best_inds[0].second;

        _best_ind.print();
        cout << "Rank: " << _best_rank << endl;

        Population<Ind> new_population;

        for (int i = 0; i < _population_zero.get_size(); i++) {
            if (i < best_inds.size()) {
                new_population.add_individual(best_inds[i].first);
                continue;
            }

            Ind ind(generate_genome(frecs));
            new_population.add_individual(ind);
        }

        _population = new_population;
    }
}

template<class Ind>
Ind UMDA<Ind>::get_best(){
    return _best_ind;
};

template<class Ind>
double UMDA<Ind>::get_rank() {
    return _best_rank;
}

template class UMDA<Individual>;
