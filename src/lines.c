// lines.c : splitting the program dump into lines and normalising them

#include "../include/lines.h"
#include "../include/tools.h"

// count the number of line
int lines_count(const char *dump)
{
	int count = 0;
	for (int i = 0; dump[i] != '\0'; i++) {
		if (dump[i] == '\n')
			count++;
	}
	return count + 1;
}

// check if the line is empty
int empty_checker(const char* line)
{
	int count = 1;
	for (int i = 0; line[i] != '\0' && count == 1; i++) {
		if (line[i] != ' ' && line[i] != '\t')
			count = 0;
	}
	return count;
}

// parsing dump on array of line
char** array_parser(const char *dump, int count_line)
{
	char** array_of_lines = (char **) malloc(count_line * sizeof(char *));
	if (array_of_lines == NULL)
		return NULL;

	int i = 0;
	for (int lines_i = 0; lines_i < count_line; lines_i++) {
		// discovering the length of the current line
		int length = 0;
		for (int k = i; dump[k] != '\n' && dump[k] != '\0'; k++)
			length++;

		// malloc the line (+1 for the null terminator)
		char* line = (char*) malloc((length + 1) * sizeof(char));
		if (line == NULL)
			return array_of_lines;

		// dumping data and terminating the string
		for (int k = 0; k < length; k++)
			line[k] = dump[i + k];
		line[length] = '\0';

		// saving line and moving past it, stepping over the newline only
		array_of_lines[lines_i] = line;
		i += length;
		if (dump[i] == '\n')
			i++;
	}
	return array_of_lines;
}

// parsing line into simplified version (removing space and tab, dropping
// anything after a ';' comment marker)
char* line_parser(const char *line, char* big_word)
{
	(void) big_word;

	// the parsed line is never longer than the original
	int length = my_strlen(line);
	char* line_parsed = (char*) malloc((length + 1) * sizeof(char));
	if (line_parsed == NULL)
		return NULL;

	// keep every usable character up to the comment marker
	int k = 0;
	for (int i = 0; line[i] != '\0' && line[i] != ';'; i++) {
		if (line[i] != ' ' && line[i] != '\t')
			line_parsed[k++] = line[i];
	}
	line_parsed[k] = '\0';

	return line_parsed;
}
