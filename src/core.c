#include "../include/core.h"

// initializing the stack with an empty plate
stack_plate first = NULL;

// initializing the counter of the stack
int plates_count = 0;

// check if the file have an exit function
int exit_looker(char** array_of_lines, int count_line)
{
	for (int i = 0; i < count_line; i++) {
		if (!strcmp(array_of_lines[i], "exit"))
			return 1;
	}
	return 0;
}

// saving the two parameters in two strings
void save_parameter(const char *instruction, char** first_parameter_p, char** second_parameter_p, int offset)
{
	int f_parameter_length = 0;
	int s_parameter_length = 0;

	for (int i = offset; instruction[i] != '(' && instruction[i] != '\0'; i++, f_parameter_length++);

	char *first_parameter = (char*) malloc((f_parameter_length + 1) * sizeof(char));

	for (int i = 0, k = offset; i < f_parameter_length; i++, k++)
		first_parameter[i] = instruction[k];

	first_parameter[f_parameter_length] = '\0';

	// TODO : -Manage the error when we have character behind ')'
	for (int i = offset; instruction[i] != ')' && instruction[i] != '\0'; i++, s_parameter_length++);

	s_parameter_length -= f_parameter_length + 1;

	char *second_parameter = (char*) malloc((s_parameter_length + 1) * sizeof(char));

	for (int k = f_parameter_length + offset + 1, i = 0; i < s_parameter_length; i++, k++)
		second_parameter[i] = instruction[k];

	second_parameter[s_parameter_length] = '\0';

	*first_parameter_p = first_parameter;
	*second_parameter_p = second_parameter;
}

void launch_assert(double value, enum mode mode)
{
	if (mode == FUNC)
		assert_function(first, value);
}

int assert_checker(char **first_parameter, double value, int *error, enum mode mode)
{
	if (!strcmp(*first_parameter, "int8") || !strcmp(*first_parameter, "int16") ||
		!strcmp(*first_parameter, "int32") || !strcmp(*first_parameter, "float") ||
		!strcmp(*first_parameter, "double")) {
		launch_assert(value, mode);
		return 0;
	}
	*error = -1;
	return -1;
}

// calling assert function with the good arguments
int assert_parameter(const char *instruction, char **first_parameter, char **second_parameter, int offset, enum mode mode)
{
	save_parameter(instruction, first_parameter, second_parameter, offset);
	int error = 0;
	double value = my_atof(*second_parameter);
	assert_checker(first_parameter, value, &error, mode);
	return error;
}

// calling push function with the good arguments
int push_parameter(const char *instruction, char **first_parameter, char **second_parameter, int offset, enum mode mode)
{
	save_parameter(instruction, first_parameter, second_parameter, offset);
	int error = 0;
	double value = my_atof(*second_parameter);
	if (!strcmp(*first_parameter, "int8")) {
		if (mode == FUNC) {
			first = push_function(first, value, INT_8);
			plates_count++;
		}
	} else if (!strcmp(*first_parameter, "int16")) {
		if (mode == FUNC) {
			first = push_function(first, value, INT_16);
			plates_count++;
		}
	} else if (!strcmp(*first_parameter, "int32")) {
		if (mode == FUNC) {
			first = push_function(first, value, INT_32);
			plates_count++;
		}
	} else if (!strcmp(*first_parameter, "float")) {
		if (mode == FUNC) {
			first = push_function(first, value, FLOAT);
			plates_count++;
		}
	} else if (!strcmp(*first_parameter, "double")) {
		if (mode == FUNC) {
			first = push_function(first, value, DOUBLE);
			plates_count++;
		}
	} else
		error = -1;

	return error;
}

// detecting and calling the function on the file -> in two mode syntax and func
int instruction_parameter(const char *instruction, enum mode mode)
{
	char *first_parameter = NULL;
	char *second_parameter = NULL;
	int error;

	if (instruction[0] == 'p' && instruction[1] == 'u' && instruction[2]  == 's' && instruction[3] == 'h')
		error = push_parameter(instruction, &first_parameter, &second_parameter, 4, mode);
	else if (instruction[0] == 'a' && instruction[1] == 's' && instruction[2]  == 's' && instruction[3] == 'e' && instruction[4] == 'r' && instruction[5] == 't') {
		error = assert_parameter(instruction, &first_parameter, &second_parameter, 6, mode);
	} else
		error = -1;

	free(first_parameter);
	free(second_parameter);
	return error;
}

// detecting and calling the function on the file -> in two mode syntax and func
void instruction_one(const char *instruction, int *error, enum mode mode)
{
	if (!strcmp(instruction, "pop")) {
		if (mode == FUNC && plates_count > 0) {
			first = pop_function(first);
			plates_count--;
		} else if (mode == FUNC) {
			my_putstr("Error when using pop function : the stack doesnt have enough plates\n");
			*error = -4;
		}
	} else if (!strcmp(instruction, "add")) {
		if (mode == FUNC && plates_count > 1) {
			first = add_function(first);
			plates_count--;
		} else if (mode == FUNC) {
			my_putstr("Error when using add function : the stack doesnt have enough plates\n");
			*error = -4;
		}
	} else if (!strcmp(instruction, "sub")) {
		if (mode == FUNC && plates_count > 1) {
			first = sub_function(first);
			plates_count--;
		} else if (mode == FUNC) {
			my_putstr("Error when using sub function : the stack doesnt have enough plates\n");
			*error = -4;
		}
	} else if (!strcmp(instruction, "mul")) {
		if (mode == FUNC && plates_count > 1) {
			first = mul_function(first);
			plates_count--;
		} else if (mode == FUNC) {
			my_putstr("Error when using mul function : the stack doesnt have enough plates\n");
			*error = -4;
		}
	} else if (!strcmp(instruction, "div")) {
		if (mode == FUNC && plates_count > 1) {
			first = div_function(first);
			plates_count--;
		} else if (mode == FUNC) {
			my_putstr("Error when using div function : the stack doesnt have enough plates\n");
			*error = -4;
		}
	} else if (!strcmp(instruction, "mod")) {
		if (mode == FUNC && plates_count > 1) {
			first = mod_function(first);
			plates_count--;
		} else if (mode == FUNC) {
			my_putstr("Error when using mod function : the stack doesnt have enough plates\n");
			*error = -4;
		}
	} else
		*error = -1;
}

// detecting and calling the function in the file -> in two mode syntax and func
void instruction_two(const char *instruction, int *error, enum mode mode)
{
	if (!strcmp(instruction, "exit")) {
		if (mode == FUNC)
			*error = -2;
	} else if (!strcmp(instruction, "dump")) {
		if (mode == FUNC && plates_count > 0)
			dump_function(first);
	} else
		*error = -1;
}

// detecting and calling the function in the file -> in two mode syntax and func
void instruction_three(const char *instruction, int *error, enum mode mode)
{
	if (!strcmp(instruction, "print")) {
		if (mode == FUNC)
			print_function(first);
	} else
		*error =  -1;
}

// detecting and calling the function in the file -> in two mode syntax and func
// we are using the length of the line to manage our function finding faster
int instruction_finder(const char *instruction, enum mode mode)
{
	int length = my_strlen(instruction);
	int error = 0;
	if (length == 3)
		instruction_one(instruction, &error, mode);
	else if (length == 4)
		instruction_two(instruction, &error, mode);
	else if (length == 5)
		instruction_three(instruction, &error, mode);
	else if (length > 5) {
		if (instruction_parameter(instruction, mode) == -1)
			error = -1;
	} else
		error = -1;

	return error;
}

// checking the syntax of the file
int instruction_syntax(char** array_of_lines, const char *dump, int count_line, enum mode mode)
{
	int error = 0;
	for (int i = 0; i < count_line; i++) {
		if (empty_checker(array_of_lines[i]) == 0) {
			error = instruction_finder(array_of_lines[i], mode);
			if (error == -1) {
				my_putstr("Error syntax on line : ");
				my_putnbr(i + 1);
				my_putchar('\n');
				print_line(dump, i + 1);
				return -1;
			} else if (error == -2)
				return 0;
			else if (error == -4) {
				my_putstr("Error on line : ");
				my_putnbr(i + 1);
				my_putchar('\n');
				print_line(dump, i + 1);
				return -1;
			}
		}
	}
	return error;
}

// freeing an array of string
void free_array(char** array_of_lines, int count_line)
{
	for (int i = 0; i < count_line; i++)
		free(array_of_lines[i]);
	free(array_of_lines);
}

// checking the syntax and after that launching function
int syntax_looker(const char *dump, char* file_name)
{
	int count_line = lines_count(dump);
	char* big_word = NULL;

	// saving the file in a array of string
	char** array_of_lines = array_parser(dump, count_line);
	if (array_of_lines == NULL)
		return -1;

	// parsing the array for simplifying the syntax checking, replacing each
	// raw line with its normalised version and freeing the raw one
	for (int i = 0; i < count_line; i++) {
		char* parsed = line_parser(array_of_lines[i], big_word);
		free(array_of_lines[i]);
		array_of_lines[i] = parsed;
	}

	if (exit_looker(array_of_lines, count_line) == 0) {
		my_putstr("You must specify a end instruction in ");
		my_putstr(file_name);
		my_putchar('\n');
		free_array(array_of_lines, count_line);
		return -1;
	}

	// launching the syntax checking
	if (instruction_syntax(array_of_lines, dump, count_line, SYNTAX) == -1) {
		free_array(array_of_lines, count_line);
		return -1;
	}

	// launching functions
	instruction_syntax(array_of_lines, dump, count_line, FUNC);

	// freeing the stack and the array of strings
	first = free_stack(first);
	free_array(array_of_lines, count_line);
	return 0;
}

int process_arg(int argc, char **argv)
{
	if (argc > 1 && argc < 3) {
		int length_file = file_length(argv[1]);

		// dumping the file content on a string
		char* file_dump = file_dumper(argv[1], length_file);

		if (length_file > 0 && file_dump != NULL) {
			syntax_looker(file_dump, argv[1]);
			free(file_dump);
			return 0;
		}
		free(file_dump);
		my_putstr("The specified file doesnt exist or is empty : ");
		my_putstr(argv[1]);
		my_putchar('\n');
		return 0;
	}
	my_putstr("Invalid number of argument : Information\n");
	return -1;
}
