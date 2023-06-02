#include <stdio.h>

void print_file(char filename);

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        print_file(argv[i]);
    }
    return 0;
}

void print_file(char filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char c = getchar();
        while (c != EOF) {
            putchar(c);
            c = getchar();
        }
    }
}