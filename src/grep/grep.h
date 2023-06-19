#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_h;
  int flag_s;
  int flag_f;
  int flag_o;
  int error;
} options;

void grep_programm(int argc, char** argv);
void print_file(char* filename, options* option);
int parser_option(int argc, char** argv, options* option);

#endif
