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


void train(char * argv[]) {
    vector<SAMPLE> X;
    vector<SAMPLE> Y;
    int x_sizes = 4; // Tamaño de caracteristicas por cada x
    read_trainingset(argv[2], x_sizes, X, Y);

    vector<unsigned int> layers_sizes = {8, 16, 1}; // Neuronas por capa
    // vector<unsigned int> layers_sizes = {8, 16, 8, 3, 1}; // Neuronas por capa
    MLP mlp(layers_sizes, x_sizes);
    mlp.set_config(Activation::SIGMOID, F_Cost::ECM, 0.01);
    mlp.show_config();
    cout << "Last Error: " << mlp.train(X, Y) << endl;
    mlp.export_errors();
    mlp.export_model();
}


void test(char * argv[]) {
    MLP mlp("model.txt");
    mlp.show_config();


    vector<SAMPLE> X;
    vector<SAMPLE> Y;
    int x_sizes = 4; // Tamaño de caracteristicas por cada x

    read_trainingset(argv[2], x_sizes, X, Y);

    int correct = 0;

    vector<vector<double>> output = mlp.predict(X);

    for (unsigned int i = 0; i < output.size(); i++) {
        for (unsigned int j = 0; j < output[i].size(); j++) {
            if (output[i][j] >= 0.5) {
                output[i][j] = 1.0;
            }
        }

        bool equals = true;
        for (unsigned int j = 0; j < Y[i].size(); j++) {
            if (Y[i][j] != output[i][j]) {
                equals = false;
                break;
            }
        }

        if(equals) {
            correct ++;
        }
    }

    cout << "Accuracy: " << (double)correct / Y.size() << endl;
}


int main(int argc, char * argv[]) {
    if (argc < 2) {
        cout << "Missing args: [training_set file name]" << endl;
        exit(EXIT_FAILURE);
    }
    const string option = argv[1];

    if (option == "-train") {
        train(argv);
    } else if (option == "-test") {
        test(argv);
    } else {
        cout << "invalid option: " << option << endl;
    }

    return 0;
}
