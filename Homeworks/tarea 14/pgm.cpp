/**
    ANSI C standard: c11
    main.c
    Purpose: Read and write images type pgm P2

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <cstdio>
#include <cstdlib>
#include "pgm.hpp"


/* Reade the img file */
pgmImage read_pgmImage(const char * file_name) {
    pgmImage img;
    img.comment = img.format = NULL;
    img.max_gray_value = img.width = img.height = 0;
    char *comment = NULL;
    size_t str_buf_size = 0;
    ssize_t str_len = 0;

    FILE * fp = fopen(file_name, "rb");
    if (fp == NULL) {
        perror(file_name);
        return img;
    }

    // Read first line containing the image format
    str_len = getline(&img.format, &str_buf_size, fp);
    if ( str_len < 3 || img.format[0] != 'P' || (img.format[1] != '2' && img.format[1] != '5')) {
        puts("Invalid format header");
        fclose(fp);
        return img;
    }

    // Read the comment if exists
    str_len = getline(&comment, &str_buf_size, fp);
    // Exists a comment
    if(str_len && comment[0] == '#') {
        img.comment = comment;
        // Read the img dimensions
        fscanf(fp, "%d %d\n", &img.width, &img.height);
    } else {
        // 'commment' contains the first row with the img pixels
        sscanf(comment, "%d %d\n", &img.width, &img.height);
        free(comment);
    }

    fscanf(fp, "%d\n", (int *)&img.max_gray_value);

    // Allocate memory to read the img content

    // Read the pixels values
    if (img.format[1] == '2') {
        // Read the img pixels for magic code P2
        int tmp;
        for (int i = 0; i < img.height; i++) {
            vector<unsigned char> row;
            for (int j = 0; j < img.width; j++) {
                fscanf(fp, "%d", &tmp);
                row.push_back((unsigned char)tmp);
            }
            img.content.push_back(row);
        }
    } else {
        // Read the img pixels for magic code P5
        unsigned char tmp;
        for (int i = 0; i < img.height; i++) {
            vector<unsigned char> row;
            for (int j = 0; j < img.width; j++) {
                fscanf(fp, "%c", &tmp);
                row.push_back(tmp);
            }
            img.content.push_back(row);
        }
    }

    fclose(fp);

    return img;
}

/* Save a pgmImage struct into .pgm file*/
void write_pgmImage(pgmImage img, const char * file_name) {
    FILE * fp = fopen(file_name, "w+");
    if (fp == NULL) {
        perror(file_name);
        return;
    }

    fprintf(fp, "%s", img.format);

    if (img.comment != NULL) {
        fprintf(fp, "%s", img.comment);
    }

    fprintf(fp, "%d %d\n", img.width, img.height);
    fprintf(fp, "%d\n", img.max_gray_value);

    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            if (img.format[1] == '2') {
                fprintf(fp, "%d ", img.content[i][j]);
            } else {
                fprintf(fp, "%c", img.content[i][j]);
            }
        }
        if (img.format[1] == '2') {
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
}

/* Liberate the memory allocated for pgm image */
void free_pgmImage(pgmImage * img) {
    if (img->format != NULL) {
        free(img->format);
        img->format = NULL;
    }

    if (img->comment != NULL) {
        free(img->comment);
        img->comment = NULL;
    }
}
