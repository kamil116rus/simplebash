CC = gcc
FLAGS = -Wall -Werror -Wextra


all: cat clang git


cat: cat.c cat.h
	$(CC) $(FLAGS) cat.c -o $@

git:
	git add .
	git commit -m"make commit"
	git push origin main

clang:
	clang-format -i *.c *.h

rebuild: clean all

clean: 
	rm -rf *.o  a.out 