/**
    ANSI C standard: c11
    main.c
    Purpose: Tarea 5

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "ccv_parser.h"

using namespace std;


/*
    Transform a character to lowercase,
    remove tildes, and transform non alphabetic characters
    to spaces
*/
char parse_char(char c) {
    // Upercase to lowercase
    if (65 <= c && c <= 90) {
        return c + 32;
    }
    // Lowercase or digit
    if ((97 <= c && c <= 122) || ('0' <= c && c <= '9')) {
        return c;
    }

    // Compare the second part of the ascci representation for especial chars
    // The first part is equals to -61

    // Á or á to a
    if (c == -127 || c == -95) {
        return 'a';
    }
    // É or é to e
    if (c == -119 || c == -87) {
        return 'e';
    }
    // Í or í to i
    if (c == -115 || c == -83) {
        return 'i';
    }
    // Ó or ó to o
    if (c == -109 || c == -77) {
        return 'o';
    }
    // Ú or ú to u
    if (c == -102 || c == -70) {
        return 'u';
    }
    // Ü or ü to u
    if (c == -100 || c == -68) {
        return 'u';
    }

    // Ñ or ñ to n
    if (c == -111 || c == -79) {
        return 'n';
    }

    return ' ';
}

/* Remove tildes and other weird things */
string parse_str(string str) {
    string str_clean = "";
    char c;
    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] == -61) continue; // Indicates the beginning of a weird thing
        c = parse_char(str[i]);
        if (c == ' ') continue;

        str_clean += c;
    }

    return str_clean;
}


frequencyMap load_ccv_freqs_map(const string file_name) {
    ifstream infile(file_name);
    if (!infile.is_open()) {
        cout << "Unable to open the file " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    frequencyMap frecs;
    string line, type, word;

    getline(infile, line); // Jump labels

    while (!infile.eof()) {
        getline(infile, line);
        if (line == "") continue;

        stringstream sstrm1(line);

        getline(sstrm1, type, ',');
        getline(sstrm1, line);

        bool is_spam = (type == "spam")? true: false;

        stringstream sstrm2(line);
        while( sstrm2 >> word) {
            word = parse_str(word);
            if (word.size() <= 3) continue;
            if (is_spam) {
                frecs[word].first++;
            } else {
                frecs[word].second++;
            }
        }
    }

    infile.close();

    return frecs;
}

/*
    Returns a vector with theand type (spam or not) for
    the email and the words to clasified
*/
vector<pair<bool, vector<string>> > load_ccv_test(const string file_name) {
    vector<pair<bool, vector<string>> > test;

    ifstream infile(file_name);
    if (!infile.is_open()) {
        cout << "Unable to open the file " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    string line, type, word;
    getline(infile, line); // Jump labels

    while (!infile.eof()) {
        getline(infile, line);
        if (line == "") continue;

        stringstream sstrm1(line);

        getline(sstrm1, type, ',');
        getline(sstrm1, line);

        bool is_spam = (type == "spam")? true: false;
        vector<string> text;
        map<string, int> words;
        map<string, int>::iterator it;

        stringstream sstrm2(line);
        while( sstrm2 >> word) {
            word = parse_str(word);
            if (word.size() <= 3) continue;
            words[word] ++;
        }
        for (it = words.begin(); it != words.end(); it++) {
            text.push_back(it->first);
        }

        test.push_back(make_pair(is_spam, text));
    }

    infile.close();

    return test;
}
