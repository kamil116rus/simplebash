#include "cat.h"

#include <stdio.h>

int main(int argc, char** argv) {
    options option = {0};
    int file_number;
    file_number = parser_option(argc, argv, &option);
    // printf("%s", argv[file_number]);
    if (option.error == 0) {
        for (; file_number < argc; file_number++) {
            print_file(argv[file_number], &option);
        }
    }
    return (option.error) ? 1 : 0;
}

void print_file(char* filename, options* option) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        int c, prev;
        int squeeze = 0;
        for (; (c = fgetc(file)) != EOF; prev = c) {
            if (option->flag_s == 1) {
                if (prev == '\n' && c == '\n' && squeeze == 0) {
                    squeeze = 1;
                } else if (squeeze == 1 && c == '\n' && prev == '\n')
                    continue;
                else if (squeeze == 1 && prev == '\n' && c != '\n')
                    squeeze = 0;
            }
            if (option->flag_n == 1 && option->flag_b == 0) printf("%6d\t", option->flag_n++);
            if (option->flag_b == 1 && c != '\n')
                printf("%6d\t", option->flag_b++);
            else if (option->flag_b > 1 && prev == '\n' && c != '\n')
                printf("%6d\t", option->flag_b++);
            if (option->flag_n > 0 && option->flag_b == 0 && prev == '\n') printf("%6d\t", option->flag_n++);
            if (option->flag_t == 1 && c == '\t') {
                printf("^I");
                continue;
            }
            if (option->flag_e == 1 && c == '\n') printf("$");
            if (option->flag_v == 1) {
                if (c >= 0 && c <= 31 && c != '\t' && c != '\n') {
                    printf("^");
                    c = c + 64;
                }
                if (c == 127) {
                    printf("^");
                    c = c - 64;
                }
                if (c >= 128 && c <= 159) {
                    printf("M-^");
                    c = c - 64;
                } else if (c > 159 && c < 255) {
                    printf("M-");
                    c = c - 128;
                }
                if (c == 255) {
                    printf("M-");
                    c = c - 192;
                }
            }
            putchar(c);
        }
        fclose(file);
    } else {
        fprintf(stderr, "cat: %s: No such file or directory\n", filename);
    }
}

int parser_option(int argc, char** argv, options* option) {
    const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                          {"number", no_argument, NULL, 'n'},
                                          {"squeeze-blank", 0, 0, 's'},
                                          {0, 0, 0, 0}};
    int flag = 0;

    while ((flag = getopt_long(argc, argv, "AbeEnstTv", long_options, NULL)) != -1) {
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
            option->flag_t = 1;
        else if (flag == 'v')
            option->flag_v = 1;
        else {
            option->error = 1;
        }
    }
    return optind;
}
