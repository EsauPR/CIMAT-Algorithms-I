#include <iostream>
#include <fstream>
#include <sstream>

#include "mlp.hpp"

using namespace std;


TRAINING_SET read_trainingset(const string file_name, unsigned int x_size) {
    ifstream input(file_name);
    if (!input.is_open()) {
        cout << "File " << file_name << " not found" << endl;
        exit(EXIT_FAILURE);
    }

    TRAINING_SET training_set;
    string line;
    getline(input, line); // Jump first line

    while(!input.eof()) {
        SAMPLE sample;
        double y;

        getline(input, line);
        stringstream ss(line);

        for (unsigned int i = 0; i < x_size; i++) {
            if (input.eof()) {
                return training_set;
            }

            double value;
            ss >> value;
            sample.push_back(value);
        }

        ss >> y;

        training_set.push_back(make_pair(sample, y));
    }

    return training_set;
}


int main(int argc, char * argv[]) {
    if (argc < 2) {
        cout << "Missing args: [training_set file name]" << endl;
        exit(EXIT_FAILURE);
    }

    int x_sizes = 4;
    TRAINING_SET trainig_set = read_trainingset(argv[1], x_sizes);

    // for (int i = 0; i < trainig_set.size(); i++) {
    //     for (int j = 0; j < trainig_set[i].first.size(); j++){
    //         cout << trainig_set[i].first[j] << " ";
    //     }
    //     cout << trainig_set[i].second << endl;
    // }

    int sizes[] = {3, 4, 5, 2, 3};
    vector<unsigned int> layers_sizes(sizes, sizes + sizeof(sizes) / sizeof(int));
    MLP mlp(layers_sizes, x_sizes);
    mlp.train(trainig_set);

    return 0;
}
