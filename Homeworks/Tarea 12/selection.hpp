/**
    C++ standard: c++11
    selection.hpp
    Purpose: Prototype for Selection class

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <vector>

using namespace std;

#ifdef SELECTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

class Selection {
    private:
        template <typename Ind>
        static double _get_repr(Ind ind, double from=-30, double to=30);
        template <typename Ind>
        static double _h1_function_cost(Ind ind);
        template <typename Ind>
        static double _h2_function_cost(Ind ind);

    public:
        enum {
            _H1,
            _H2
        };

        template <typename Ind>
        static vector<pair<Ind, double>> select_kbest(vector<Ind> population, unsigned int f_cost_t, unsigned int kbest=10);

};


#undef SELECTION_HPP
#undef EXTERN
#endif
