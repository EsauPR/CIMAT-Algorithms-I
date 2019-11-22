#include <iostream>
#include <fstream>
#include <sstream>
#include "mlp.hpp"

using namespace std;


void read_trainingset(const string file_name, unsigned int x_size, vector<SAMPLE> &X, SAMPLE &Y) {
    ifstream input(file_name);
    if (!input.is_open()) {
        cout << "File " << file_name << " not found" << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    getline(input, line); // Jump first line

    while(!input.eof()) {
        SAMPLE sample;
        double y;

        getline(input, line);
        stringstream ss(line);

        for (unsigned int i = 0; i < x_size; i++) {
            if (input.eof()) {
                return;
            }

            double value;
            ss >> value;
            sample.push_back(value);
        }
        ss >> y;

        X.push_back(sample);
        Y.push_back(y);
    }
}


int main(int argc, char * argv[]) {
    if (argc < 2) {
        cout << "Missing args: [training_set file name]" << endl;
        exit(EXIT_FAILURE);
    }

    int x_sizes = 4;
    vector<SAMPLE> X;
    SAMPLE Y;

    read_trainingset(argv[1], x_sizes, X, Y);

    int sizes[] = {3, 4, 5, 2, 3};
    vector<unsigned int> layers_sizes(sizes, sizes + sizeof(sizes) / sizeof(int));

    MLP mlp(layers_sizes, x_sizes);
    mlp.train(X, Y);

    return 0;
}
