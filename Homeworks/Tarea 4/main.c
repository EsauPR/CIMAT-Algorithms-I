/**
    ANSI C standard: c11
    main.c
    Purpose: Read and write images type pgm P2

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>


/* Struct for pgm images */
const struct pgmStruct {
    unsigned char ** content;
    char * comment;
    char * format;
    int height;
    int width;
    unsigned char max_gray_value;

} pgmImageDefault = {NULL, NULL, NULL, 0, 0, 0};

typedef struct pgmStruct pgmImage;

/* Create memory to store the image pixels */
unsigned char ** allocate_pgmImage_content(int height, int width);
/* Reade the img file */
pgmImage read_pgmImage(const char * file_name);
/* Save a pgmImage struct into .pgm file*/
void write_pgmImage(pgmImage img, char * file_name);
/* Liberate the memory allocated for pgm image */
void free_pgmImage(pgmImage * img);


/* Create memory to store the image pixels */
unsigned char ** allocate_pgmImage_content(int height, int width) {
    unsigned char ** content = (unsigned char **)malloc(sizeof(unsigned char *) * height);
    if (content == NULL) {
        perror("allocate_pgmImage_content()");
        exit(EXIT_FAILURE);
    }

    *content = (unsigned char *)malloc(sizeof(unsigned char) * height * width);
    if (*content == NULL) {
        perror("allocate_pgmImage_content()");
        free(content);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < height; i++) {
        content[i] = &(*content)[width * i];
    }

    return content;
}

/* Reade the img file */
pgmImage read_pgmImage(const char * file_name) {
    pgmImage img = pgmImageDefault;
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
    img.content = allocate_pgmImage_content(img.height, img.width);

    // Read the pixels values
    if (img.format[1] == '2') {
        // Read the img pixels for magic code P2
        int tmp;
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                fscanf(fp, "%d", &tmp);
                img.content[i][j] = tmp;
            }
        }
    } else {
        // Read the img pixels for magic code P5
        char *line = NULL;
        str_buf_size = 0;
        str_len = getline(&line, &str_buf_size, fp);
        for (int j = 0; j < img.height * img.width; j++) {
            (*img.content)[j] = line[j];
        }
        free(line);
    }

    fclose(fp);

    return img;
}

/* Save a pgmImage struct into .pgm file*/
void write_pgmImage(pgmImage img, char * file_name) {
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

    if (img->content != NULL) {
        free(*(img->content));
        free(img->content);
        img->content = NULL;
    }
}


int main(int argc, char const *argv[]) {
    if (argc < 2) {
        puts("Missing Args: [file name]");
        exit(EXIT_FAILURE);
    }

    printf("Reading image %s...\n", argv[1]);
    pgmImage img = read_pgmImage(argv[1]);

    if (img.content == NULL) {
        free_pgmImage(&img);
        exit(EXIT_FAILURE);
    }

    char copy_name[] = "copy.pgm";
    printf("Writing a copy to %s...\n", copy_name);
    write_pgmImage(img, copy_name);

    free_pgmImage(&img);

    exit(EXIT_SUCCESS);
}
