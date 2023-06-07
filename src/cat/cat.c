#include "cat.h"

#include <stdio.h>

void print_file(char* filename);
int parser_option(int argc, char** argv, options* option);

int main(int argc, char** argv) {
    options option = {0};
    int file_number;
    file_number = parser_option(argc, argv, &option);
    for (int i = 1; i < argc; i++) {
        print_file(argv[i]);
    }
    return 0;
}

void print_file(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char c = fgetc(file);
        while (c != EOF) {
            putchar(c);
            c = fgetc(file);
        }
    }
}

int parser_option(int argc, char** argv, options* option) {
    static struct option long_options[] = {{"--number-nonblank", 0, 0, 'b'},
                                           {"--number", 0, 0, 'n'},
                                           {"--squeeze-blank)", 0, 0, 's'},
                                           {0, 0, 0, 0}};
    int flag = 0;

    while (flag = getopt_long(argc, argv, "AbeEnstTv", long_options, NULL) != -1) {
        if (flag == 'A')
            option->flag_v = option->flag_e = option->flag_t = 1;
        else if (flag == 'b')
            option->flag_b = 1;
        else if (flag == 'e')
            option->flag_e = option->flag_v = 1;
        else if (flag == 'E')
            option->flag_e = 1;
        else if (flag == 'n')
            option->flag_n = 1;
        else if (flag == 's')
            option->flag_s = 1;
        else if (flag == 't')
            option->flag_t = option->flag_v = 1;
        else if (flag == 'T')
            option->flag_e = 1;
        else if (flag == 'v')
            option->flag_v = 1;
        else
            option->error = 1;
    }
    return optind;
}