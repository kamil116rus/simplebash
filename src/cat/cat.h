#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int flag_b;
    int flag_e;
    int flag_n;
    int flag_s;
    int flag_t;
    int flag_v;
    int error;
} options;

void print_file(char* filename, options* option);
int parser_option(int argc, char** argv, options* option);

#endif
