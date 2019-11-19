#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define INDIVIDUAL_IMPORT
#include "individual.hpp"

using namespace std;

Individual::Individual() {}

Individual::Individual(unsigned int size, bool ramdonize=true) {
    _genome.resize(size, 0);
    if(!ramdonize) return;

    for (unsigned int i = 0; i < size; i++) {
        _genome[i] = rand() % 2 == 0;
    }
}

Individual::Individual(vector<bool> genome) {
    _genome = genome;
}

vector<bool> Individual::get_genome() {
    return _genome;
}

uint Individual::get_size() {
    return _genome.size();
}

bool Individual::get_at(unsigned int index) {
    return _genome[min(index, get_size() - 1)];
}

void Individual::print() {
    for (unsigned int i = 0; i < get_size(); i++) {
        cout << _genome[i] << " ";
    }
    cout << endl;
}
