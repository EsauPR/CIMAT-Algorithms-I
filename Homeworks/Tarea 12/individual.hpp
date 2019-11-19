/**
    C++ standard: c++11
    individuall.hpp
    Purpose: Prototype for individual class

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <vector>

using namespace std;

#ifdef INDIVIDUAL_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

class Individual {
    private:
        vector<bool> _genome;

    public:
        Individual();
        Individual(unsigned int size, bool ramdonize);
        Individual(vector<bool> genome);

        vector<bool> get_genome();
        unsigned int get_size();
        bool get_at(unsigned int index);
        void print();

};


#undef INDIVIDUAL_HPP
#undef EXTERN
#endif
