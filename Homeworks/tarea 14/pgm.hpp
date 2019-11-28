/**
    ANSI C standard: c11
    main.c
    Purpose: Prototype to read and write images type pgm P2

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <vector>

using namespace std;

typedef struct pgmStruct {
    vector<vector<unsigned char> > content;
    char * comment;
    char * format;
    int height;
    int width;
    unsigned char max_gray_value;

} pgmImage;


/* Reade the img file */
pgmImage read_pgmImage(const char * file_name);
/* Save a pgmImage struct into .pgm file*/
void write_pgmImage(pgmImage img, const char * file_name);
/* Liberate the memory allocated for pgm image */
void free_pgmImage(pgmImage * img);
