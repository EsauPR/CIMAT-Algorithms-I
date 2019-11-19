/**
    C++ standard: c++11
    main.cpp
    Purpose: Tarea 12

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <iostream>
#include "individual.hpp"
#include "umda.hpp"

using namespace std;



int main() {
    int population_size = 50;
    int individual_size = 10;
    int kbest = 10;
    int max_iter = 100;

    Population<Individual> population(population_size, individual_size);
    UMDA<Individual> umda(population);

    // _H1 is f(x) = x*x+13.6
    umda.run(umda._H1, kbest, max_iter);

    cout << "\nBest:\n";
    umda.get_best().print();
    cout << "Rank " << umda.get_rank() << endl;

    cout << "\n---------------------------------\n" << endl;

    // _H2 is f(x) = x*x*sin(x)
    umda.run(umda._H2, kbest, max_iter);

    cout << "\nBest:\n";
    umda.get_best().print();
    cout << "Rank " << umda.get_rank() << endl;

    return 0;
}
