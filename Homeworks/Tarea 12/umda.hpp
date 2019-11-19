#ifndef UMDA_HPP
#define UMDA_HPP

#include <vector>
#include "selection.hpp"
#include "population.hpp"

using namespace std;

#ifdef UMDA_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

template <class Ind>
class UMDA {
    private:
        Population<Ind> _population_zero;
        Population<Ind> _population;
        Ind _best_ind;
        double _best_rank;

        vector<bool> generate_genome(vector<int> frecs);
        vector<int> _get_frequencies();

    public:
        enum {
            _H1 = Selection::_H1,
            _H2 = Selection::_H2
        };

        UMDA(Population<Ind> population);

        void run(unsigned int f_cost_t, unsigned int kbest=10, unsigned int max_iters=100);
        Ind get_best();
        double get_rank();
};

#undef UMDA_HPP
#undef EXTERN
#endif
