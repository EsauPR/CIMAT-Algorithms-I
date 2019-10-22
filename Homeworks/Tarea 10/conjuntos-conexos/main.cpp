/**
    C++ standard: c11
    main.c
    Purpose: Find

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "pgm.h"

using namespace std;

#define WHITE 255
#define BLACK 0
#define VISITED 125

#define vvuc vector<vector<unsigned char> >
#define viii vector<pair<int, pair<int, int> > >

/* The 8 movs */
const int MOVS[] = {0, 1, 0, -1, 1, 0, -1, 0, 1, 1, -1, -1, 1, -1, -1, 1};

/* Return true if the positions is valid */
bool is_valid_position(int i, int j, int width, int height) {
    if( i < 0 || j < 0 || i >= height || j >= width) {
        return 0;
    }
    return 1;
}

/* DFS */
int dfs(vvuc &img, int i, int j) {
    int npixels = 1;
    int next_i, next_j;

    img[i][j] = VISITED;

    for (int k = 0; k < 16; k+=2) {
        next_i = i + MOVS[k];
        next_j = j + MOVS[k + 1];
        if (!is_valid_position(next_i, next_j, img[0].size(), img.size())) continue;
        if (img[next_i][next_j] != VISITED && img[next_i][next_j] != BLACK) {
            npixels += dfs(img, next_i, next_j);
        }
    }

    return npixels;
}

/*
    Find the components and returns a vector with the quantity of pixels
    and any positions
*/
viii find_components(vvuc &img) {
    viii results;
    for (int i = 0; i < (int)img.size(); i++) {
        for (int j = 0; j < (int)img[0].size(); j++) {
            if (img[i][j] != VISITED && img[i][j] != BLACK) {
                results.push_back(make_pair(dfs(img, i, j), make_pair(i, j)));
            }
        }
    }

    sort(results.begin(), results.end());

    return results;
}

/* Change the color to a visited component */
void paint(vvuc &img, int i, int j, int color) {
    int next_i, next_j;

    img[i][j] = color;

    for (int k = 0; k < 16; k+=2) {
        next_i = i + MOVS[k];
        next_j = j + MOVS[k + 1];
        if (!is_valid_position(next_i, next_j, img[0].size(), img.size())) continue;
        if (img[next_i][next_j] == VISITED) {
            paint(img, next_i, next_j, color);
        }
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        puts("Missing Args: [file name]");
        exit(EXIT_FAILURE);
    }

    printf("Reading image %s...\n", argv[1]);
    pgmImage img = read_pgmImage(argv[1]);

    clock_t start = clock();

    viii results = find_components(img.content);

    for (int i = 0; i < (int)results.size(); i++) {
        paint(img.content, results[i].second.first, results[i].second.second, (i == 0 || i == (int)results.size() - 1)? WHITE : BLACK);
    }

    clock_t end = clock();

    cout << "Image size: " << img.height << " x " << img.width << endl;
    cout << "Processing time: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << "Number of components: " << results.size() << endl;

    cout << "Number of pixels of each element: ";
    for (int i = 0; i < (int)results.size(); i++) {
        cout << " Component " << i+1 << " " << results[i].first << "px " << endl;
    }
    cout << endl;


    string copy_name = "copy.pgm";
    cout << "Writing a copy with the max a min element to " << copy_name << endl;
    write_pgmImage(img, copy_name.c_str());

    free_pgmImage(&img);

    exit(EXIT_SUCCESS);
}
