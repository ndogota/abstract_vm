// core.h : interpreter declarations (argument handling, syntax, dispatch)

#ifndef CORE_H
#define CORE_H

#include <stdlib.h>

#include "tools.h"
#include "linked.h"
#include "lines.h"

// mode for function -> SYNTAX : verify the syntax
//                   -> FUNC : launch functions
enum mode {
	SYNTAX,
	FUNC,
};

// processing arguments functions
int process_arg(int argc, char **argv);

// processing parameters functions and sending them in stack
void save_parameter(const char *instruction, char** first_parameter_p, char** second_parameter_p, int offset);
void launch_assert(double value, enum mode mode);
int assert_checker(char **first_parameter, double value, int *error, enum mode mode);
int assert_parameter(const char *instruction, char **first_parameter, char **second_parameter, int offset, enum mode mode);
int push_parameter(const char *instruction, char **first_parameter, char **second_parameter, int offset, enum mode mode);

// syntax functions
int syntax_looker(const char *dump, char* file_name);
int instruction_parameter(const char *instruction, enum mode mode);
void instruction_one(const char *instruction, int *error, enum mode mode);
void instruction_two(const char *instruction, int *error, enum mode mode);
void instruction_three(const char *instruction, int *error, enum mode mode);
int instruction_finder(const char *instruction, enum mode mode);
int instruction_syntax(char** array_of_lines, const char *dump, int count_line, enum mode mode);
int exit_looker(char** array_of_lines, int count_line);

// cleaning functions
void free_array(char** array_of_lines, int count_line);

#endif