// lines.h : declarations for line splitting and normalisation

#ifndef LINES_H
#define LINES_H

#include <stdlib.h>

#include "tools.h"

// lines syntax processing functions
int lines_count(const char *dump);
int empty_checker(const char* line);
char** array_parser(const char *dump, int count_line);
char* line_parser(const char *line, char* big_word);

#endif