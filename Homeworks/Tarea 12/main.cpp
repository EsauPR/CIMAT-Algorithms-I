#include <iostream>
#include "individual.hpp"
#include "umda.hpp"

using namespace std;



int main() {
    int population_size = 50;
    int individual_size = 20;
    int kbest = 10;
    int mas_iter = 100;

    Population<Individual> population(population_size, individual_size);
    UMDA<Individual> umda(population);

    umda.run(umda._H1, kbest, mas_iter);

    cout << "\nBest:\n";
    umda.get_best().print();
    cout << "Rank " << umda.get_rank() << endl;

    cout << "\n---------------------------------\n" << endl;

    umda.run(umda._H2, kbest, mas_iter);

    cout << "\nBest:\n";
    umda.get_best().print();
    cout << "Rank " << umda.get_rank() << endl;

    return 0;
}
