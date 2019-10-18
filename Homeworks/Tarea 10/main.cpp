/**
    ANSI C standard: c11
    main.c
    Purpose: clasificador Bayesiano de spam para correos electrónicos

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

#define frequencyMap map<string, pair<int, int> >
#define dictionary map<string, int >


frequencyMap load_frec_map(string file_name, frequencyMap frecs, bool is_spam) {
    ifstream infile(file_name);
    if (!infile.is_open()) {
        cout << "Unable to open the file " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    while (!infile.eof()) {
        string word;
        infile >> word;
        if (word.size() <= 3) continue;
        if (is_spam) {
            frecs[word].first++;
        } else {
            frecs[word].second++;
        }
    }

    return frecs;
}


frequencyMap clean_freqs(frequencyMap frecs) {
    frequencyMap frecs_clean;
    frequencyMap::iterator it;
    for (it = frecs.begin(); it != frecs.end(); it++) {
        if (it->second.first == 0 || it->second.second == 0) continue;
        frecs_clean[it->first] = it->second;
    }

    return frecs_clean;
}

dictionary load_text(string file_name) {
    ifstream infile(file_name);
    if (!infile.is_open()) {
        cout << "Unable to open the file " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    dictionary dict;

    while (!infile.eof()) {
        string word;
        infile >> word;
        if (word.size() <= 3) continue;
        dict[word]++;
    }

    return dict;
}


bool is_spam(frequencyMap frecs, dictionary text) {
    int total_spam = 0, total_no_spam = 0;
    frequencyMap::iterator it;
    for (it = frecs.begin(); it != frecs.end(); it++) {
        total_spam += it->second.first;
        total_no_spam += it->second.second;
    }

    double prob_spam = 1.0, prob_no_spam = 1.0;
    dictionary::iterator it2;
    for (it2 = text.begin(); it2 != text.end(); it2++) {
        if (!frecs.count(it2->first)) continue;
        // cout << it2->first << endl;
        // cout << frecs[it2->first].first << "/" << total_spam << endl;
        prob_spam *= frecs[it2->first].first / total_spam;
        // cout << frecs[it2->first].second << "/" << total_no_spam << endl;
        prob_no_spam *= frecs[it2->first].second / total_no_spam;
    }

    // cout << prob_spam << " " << prob_no_spam << endl;

    return prob_spam > prob_no_spam;
}


int main(int argc, char const *argv[]) {
    if (argc < 4) {
        cout << "Missing Args";
        exit(EXIT_FAILURE);
    }

    frequencyMap frecs;
    frecs = load_frec_map(argv[1], frecs, false);
    frecs = load_frec_map(argv[2], frecs, true);
    frecs = clean_freqs(frecs);

    frequencyMap::iterator it;
    // for ( it = frecs.begin(); it != frecs.end(); it++) {
    //     cout << it->first << " " << it->second.first << " " << it->second.second << endl;
    // }

    dictionary text = load_text(argv[3]);
    // dictionary::iterator it;
    // for ( it = text.begin(); it != text.end(); it++) {
    //     cout << it->first << " " << it->second << endl;
    // }

    if (is_spam(frecs, text)) {
        cout << "The text is spam" << endl;
    } else {
        cout << "The text is not spam" << endl;
    }



    return 0;
}
