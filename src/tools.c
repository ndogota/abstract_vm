// tools.c : low level helpers (printing, parsing, file IO, math)

#include "../include/tools.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putnbr(int nb)
{
	if (nb < 0) {
		my_putchar('-');
		nb = -nb;
	}
	if (nb >= 10) {
		my_putnbr(nb / 10);
		my_putchar(nb % 10 + '0');
	}
	if (nb < 10)
		my_putchar(nb % 10 + '0');
}

void my_putdouble(double nb)
{
	int entire_part;
	int decimal_part;

	entire_part = (int)(nb / 1);
	decimal_part = (int)((nb - entire_part) * 1000000 + 0.000001);

	my_putnbr(entire_part);
	my_putchar('.');
	my_putnbr(decimal_part);
}

void my_putstr(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        my_putchar(str[i]);
}

int my_strlen(const char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0'  && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}


// converting a string to double
double my_atof(const char *string)
{
	double result = 0.0;
	int exponent = 0;
	int character;
	int sign = 1;

	if (string[0] == '-') {
		sign = -1;
		string++;
	}

	// checking if the string have a double format
	for (int i = 0; string[i] != '\0'; i++)
		if (string[i] != '-' && string[i] != '+' && string[i] != '.' && string[i] != 'e' && string[i] != 'E' && !(string[i] >= '0' && string[i] <= '9'))
			return result;

	// calculate the double to the the first point
	while ((character = (unsigned char) *string++) != '\0' && (character >= '0' && character <= '9'))
		result = result * 10.0 + (character - '0');

	// detect the point and do the same process
	if (character == '.')
		while ((character = (unsigned char) *string++) != '\0' && (character >= '0' && character <= '9')) {
			result = result * 10.0 + (character - '0');
			exponent--;
		}

	if (character == 'e' || character == 'E') {
		int exponent_sign = 1;
		int i = 0;
		character = (unsigned char) *string++;
		if (character == '+')
			character = (unsigned char) *string++;
		else if (character == '-') {
			character = (unsigned char) *string++;
			exponent_sign = -1;
		}
		while (character >= '0' && character <= '9') {
			i = i * 10 + (character - '0');
			character = (unsigned char) *string++;
		}
		exponent += i * exponent_sign;
	}

	// adding exponent multiplications to the result
	while (exponent > 0) {
		result *= 10.0;
		exponent--;
	}
	while (exponent < 0) {
		result *= 0.1;
		exponent++;
	}

	return result * sign;
}

// Reading a file and return the length of it
int file_length(char *file_path)
{
    int length = 0;
    int fd = open(file_path, O_RDONLY);

    if (fd == -1)
        return -1;

    for (char c = 0; (read(fd,&c,1)) != 0; )
        length++;

    close(fd);
    return (length);
}

// Read the whole file into a freshly allocated, null terminated string.
// Returns NULL on an empty file, an invalid length or an open/read error.
char* file_dumper(char *file_path, int length)
{
    if (length <= 0)
        return NULL;

    char *dump = (char *) malloc((length + 1) * sizeof(char));
    if (dump == NULL)
        return NULL;

    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        free(dump);
        return NULL;
    }

    char c = 0;
    int i = 0;
    while (i < length && read(fd, &c, 1) > 0)
        dump[i++] = c;
    dump[i] = '\0';

    close(fd);
    return dump;
}

// print a specific line of a file
void print_line(const char *file, int line_number)
{
	int current_line = 1;

	for (int i = 0; file[i] != '\0' && current_line <= line_number; i++) {
		if (file[i] == '\n')
			current_line++;
		if (current_line == line_number && file[i] != '\n')
			my_putchar(file[i]);
	}

	my_putchar('\n');
}

double my_pow(double x, int n)
{
	double result = 1;
	int negative = 1;

	if (n < 0) {
		negative = -1;
		n = -n;
	}

	if (0 == n)
		return 1;
	else if (0 == x)
		return 0;

	while (n) {
		if (n & 1)
			result *= x;
		x *= x;
		n /= 2;
	}

	if (negative < 0)
		return 1.0 / result;
	else
		return result;
}

// checking if the value is on good interval using bits multiplier
int check_interval(double value, int bits)
{
	if (value >= (my_pow(2, bits) / 2) * -1 && value <= (my_pow(2, bits) / 2) - 1)
		return 1;
	return 0;
}