// tools.h : declarations for the low level helpers

#ifndef TOOLS_H
#define TOOLS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

// basic functions
void my_putchar(char c);
void my_putstr(const char *str);
void my_putnbr(int nb);
void my_putdouble(double nb);
int strcmp(const char *s1, const char *s2);
int my_strlen(const char *str);
double my_atof(const char *string);

// file processing functions
int file_length(char *file_path);
char* file_dumper(char *file_path, int length);
void print_line(const char *file, int line_number);

// bits functions
int check_interval(double value, int bits);

#endif