#include <iostream>
#include <fstream>
#include <sstream>
#include "mlp.hpp"

using namespace std;


void read_trainingset(const string file_name, unsigned int x_size, vector<SAMPLE> &X, vector<SAMPLE> &Y) {
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
        vector<double> ys(1, y);

        X.push_back(sample);
        Y.push_back(ys);
    }
}


int main(int argc, char * argv[]) {
    if (argc < 1) {
        cout << "Missing args: [training_set file name]" << endl;
        exit(EXIT_FAILURE);
    }

    int x_sizes = 4;
    vector<SAMPLE> X;
    vector<SAMPLE> Y;
    read_trainingset(argv[1], x_sizes, X, Y);

    vector<unsigned int> layers_sizes = {8, 16, 1};
    MLP mlp(layers_sizes, x_sizes);
    mlp.set_config(Activation::SIGMOID, F_Cost::ECM, 0.01);
    mlp.get_config();
    mlp.train(X, Y);

    return 0;
}
