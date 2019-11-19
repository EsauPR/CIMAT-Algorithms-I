/**
    C++ standard: c++11
    population.hpp
    Purpose: Prototype for Population class

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>

using namespace std;

#ifdef POPULATION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


template <class Ind>
class Population {
    private:
        vector<Ind> _individuals;

    public:
        Population();
        Population(unsigned int p_size, unsigned int ind_size, bool ramdonize=true);

        void add_individual(Ind ind);
        Ind get_at(unsigned int index);
        unsigned int get_size();
        vector<Ind> get_individuals();
};


#undef POPULATION_HPP
#undef EXTERN
#endif
