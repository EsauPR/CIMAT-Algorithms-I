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
#include <fstream>
#include <cmath>

#include "ccv_parser.h"

using namespace std;

#define dictionary map<string, int >

/* Remove the words from the frquency map that does not have any match in spam or no spam */
frequencyMap clean_freqs(frequencyMap frecs) {
    frequencyMap frecs_clean;
    frequencyMap::iterator it;
    for (it = frecs.begin(); it != frecs.end(); it++) {
        if (it->second.first == 0 || it->second.second == 0) continue;
        frecs_clean[it->first] = it->second;
    }

    return frecs_clean;
}

/* Return a true if the text is spam or false otherwise */
bool is_spam(frequencyMap frecs, vector<string> text) {
    int total_spam = 0, total_no_spam = 0;
    frequencyMap::iterator it;
    for (it = frecs.begin(); it != frecs.end(); it++) {
        total_spam += it->second.first;
        total_no_spam += it->second.second;
    }

    double prob_spam = log2((double)total_spam / total_no_spam);
    for (int i = 0; i < (int)text.size(); i++) {
        if (frecs.count(text[i]) == 0) continue;
        double pwi_spam = (double)frecs[text[i]].first * total_no_spam;
        double pwi_no_spam = (double)frecs[text[i]].second * total_spam;
        prob_spam += log2(pwi_spam / pwi_no_spam);
        fflush(stdout);
    }

    if  (prob_spam > 0.0) return true;
    return false;
}


int main(int argc, char const *argv[]) {
    if (argc < 3) {
        cout << "Missing Args";
        exit(EXIT_FAILURE);
    }

    frequencyMap frecs = load_ccv_freqs_map(argv[1]);
    frecs = clean_freqs(frecs);

    vector<pair<bool, vector<string> > > test = load_ccv_test(argv[2]);

    int spam_spam = 0, spam_no_spam = 0;
    int no_spam_spam = 0, no_spam_no_spam = 0;
    for (int i = 0; i < (int)test.size(); i++) {
        bool sp_cls = is_spam(frecs, test[i].second);
        if (test[i].first && sp_cls) {
            spam_spam++;
        } else if (test[i].first && !sp_cls){
            spam_no_spam++;
        } else if (!test[i].first && sp_cls) {
            no_spam_spam++;
        } else {
            no_spam_no_spam++;
        }
    }

    cout << "Nunmber of spam classified as spam: " << spam_spam << endl;
    cout << "Nunmber of spam classified as not spam: " << spam_no_spam << endl;
    cout << "Nunmber of not spam classified as spam: " << no_spam_spam << endl;
    cout << "Nunmber of not spam classified as not spam: " << no_spam_no_spam << endl;
    cout << "Precision: " << (double)spam_spam / (spam_spam + no_spam_spam) << endl;
    cout << "Recall: " << (double)spam_spam / (spam_spam + spam_no_spam) << endl;
    cout << "Accuracy: " << (double)(spam_spam + no_spam_no_spam) / (spam_spam + no_spam_no_spam + no_spam_spam + spam_no_spam)<< endl;

    return 0;
}
