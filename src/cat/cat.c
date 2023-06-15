#include "cat.h"

#include <stdio.h>

void print_file(char* filename, options* option);
int parser_option(int argc, char** argv, options* option);

int main(int argc, char** argv) {
    options option = {0};
    int file_number;
    file_number = parser_option(argc, argv, &option);
    for (; file_number < argc; file_number++) {
        print_file(argv[file_number], &option);
    }
    return 0;
}

void print_file(char* filename, options* option) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char c, prev;
        for (; (c = fgetc(file)) != EOF; prev = c) {
            if (option->flag_n == 1 && option->flag_b == 0) printf("%6d\t", option->flag_n++);

            if (option->flag_b == 1 && c != '\n') printf("%6d\t", option->flag_b++);

            if (option->flag_e == 1 && option->flag_v == 1 && c == '\n') printf("$");
            if (option->flag_n > 1 && option->flag_b == 0 && prev == '\n') printf("%6d\t", option->flag_n++);

            if (option->flag_b > 0 && prev == '\n' && c != '\n') printf("%6d\t", option->flag_b++);

            putchar(c);
        }
    }
}

int parser_option(int argc, char** argv, options* option) {
    static struct option long_options[] = {{"--number-nonblank", 0, 0, 'b'},
                                           {"--number", 0, 0, 'n'},
                                           {"--squeeze-blank)", 0, 0, 's'},
                                           {0, 0, 0, 0}};
    int flag = 0;

    while ((flag = getopt_long(argc, argv, "AbeEnstTv", long_options, NULL)) != -1) {
        if (flag == 'A')
            option->flag_v = option->flag_e = option->flag_t = 1;
        else if (flag == 'b')
            option->flag_b = 1;
        else if (flag == 'e')
            option->flag_e = 1;
        else if (flag == 'E')
            option->flag_e = option->flag_v = 1;
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