#include <algorithm>
#include "individual.hpp"

#define POPULATION_IMPORT
#include "population.hpp"

using namespace std;

template <class Ind>
Population<Ind>::Population() {}

template <class Ind>
Population<Ind>::Population(unsigned int p_size, unsigned int ind_size, bool ramdonize) {
    for (int i = 0; i < p_size; i++) {
        Ind ind(ind_size, ramdonize);
        add_individual(ind);
    }
}

template <class Ind>
void Population<Ind>::add_individual(Ind ind) {
    _individuals.push_back(ind);
}

template <class Ind>
unsigned int Population<Ind>::get_size() {
    return _individuals.size();
}

template <class Ind>
Ind Population<Ind>::get_at(unsigned int index) {
    return _individuals[min(index, get_size() - 1)];
}

template <class Ind>
vector<Ind> Population<Ind>::get_individuals() {
    return _individuals;
}

template class Population<Individual>;
