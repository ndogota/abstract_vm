#include "../include/tools.h"
#include "../include/linked.h"

// get a new plate
stack_plate get_plate()
{
	stack_plate new;
	new = (stack_plate)malloc(sizeof(struct stack));
	return new;
}

// printing a node
void print_plate(struct stack *p)
{
	switch (p->type) {
		case INT_8:
			my_putnbr(p->lifo.int8_lifo);
			my_putchar('\n');
			break;
		case INT_16:
			my_putnbr(p->lifo.int16_lifo);
			my_putchar('\n');
			break;
		case INT_32:
			my_putnbr(p->lifo.int32_lifo);
			my_putchar('\n');
			break;
		case FLOAT:
			my_putdouble(p->lifo.float_lifo);
			my_putchar('\n');
			break;
		case DOUBLE:
			my_putdouble(p->lifo.double_lifo);
			my_putchar('\n');
			break;
		default:
			my_putstr("The stack is empty.\n");
			break;
	}
}

// verify the value before saving on stack
int save_value(struct stack *node, double data, enum list_type type)
{
	if (type == INT_8 && check_interval(data, 8)) {
		node->type = type;
		node->lifo.int8_lifo = (int8_t) data;
	} else if (type == INT_16 && check_interval(data, 16)) {
		node->type = type;
		node->lifo.int16_lifo = (int16_t) data;
	} else if (type == INT_32 && check_interval(data, 32)) {
		node->type = type;
		node->lifo.int32_lifo = (int32_t) data;
	} else if (type == FLOAT && check_interval(data, 32)) {
		node->type = type;
		node->lifo.float_lifo = (float) data;
	} else if (type == DOUBLE && check_interval(data, 64)) {
		node->type = type;
		node->lifo.double_lifo = (double) data;
	} else {
		my_putstr("Error when saving value in stack, incorrect value\n");
		return -3;
	}
	return 0;
}

// returning the value of the plate
double get_value(stack_plate plate)
{
	if (plate == NULL) {
		my_putstr("The plate is empty, cannot perform get_value().\n");
		return 0;
	}
	switch (plate->type) {
		case INT_8:
			return plate->lifo.int8_lifo;
		case INT_16:
			return plate->lifo.int16_lifo;
		case INT_32:
			return plate->lifo.int32_lifo;
		case FLOAT:
			return plate->lifo.float_lifo;
		case DOUBLE:
			return plate->lifo.double_lifo;
		default:
			my_putstr("The plate doesnt have value, cannot perform get_value().\n");
			return 0;
	}
}

// processing operation depending the symbol
stack_plate process_operation(stack_plate first, char symbol)
{
	stack_plate temp = NULL;

	// getting the value from the first plate
	double first_value = get_value(first);
	double first_type = first->type;

	// removing the first plate
	temp = pop_function(first);

	// getting the value from the second plate
	double second_value = get_value(temp);
	double second_type = temp->type;

	// taking the biggest type
	if (first_type < second_type) {
		first_type = second_type;
	}

	// removing the second plate
	temp = pop_function(temp);

	// pushing a new plate with the result
	switch (symbol) {
		case '+':
			temp = push_function(temp, first_value + second_value, first_type);
			break;
		case '-':
			temp = push_function(temp, second_value - first_value, first_type);
			break;
		case '*':
			temp = push_function(temp, first_value * second_value, first_type);
			break;
		case '/':
			temp = push_function(temp, second_value / first_value, first_type);
			break;
		case '%':
			temp = push_function(temp, fmod(second_value, first_value), first_type);
			break;
		default:
			my_putstr("The symbol you specify on process_operation function doesnt exist.\n");
			break;
	}

	return temp;
}

// pushing a plate with a specific data and type
stack_plate push_function(stack_plate first, double data, enum list_type type)
{
	stack_plate temp;
	temp=get_plate();
	if (save_value(temp, data, type) == -3) {
		free(temp);
		return first;
	}
	temp->next=first;
	return temp;
}

// removing the first plate
stack_plate pop_function(stack_plate first)
{
	stack_plate temp;
	if (first == NULL) {
		my_putstr("The stack is already empty, cannot perform pop().\n");
		return first;
	}
	temp=first;
	first=first->next;
	free(temp);
	return first;
}


stack_plate add_function(stack_plate first)
{
	return process_operation(first, '+');
}

stack_plate sub_function(stack_plate first)
{
	return process_operation(first, '-');
}

stack_plate mul_function(stack_plate first)
{
	return process_operation(first, '*');
}

stack_plate div_function(stack_plate first)
{
	return process_operation(first, '/');
}

stack_plate mod_function(stack_plate first)
{
	return process_operation(first, '%');
}

// verify if the value in parameter is equal to the first plate of the stack
int assert_function(stack_plate first, double value)
{
	if (get_value(first) != value) {
		my_putstr("The assert() value is not equal to the first plate.\n");
		return -1;
	}
	return 0;
}

// printing all the stack on the output
void dump_function(stack_plate first)
{
	stack_plate temp;
	if (first == NULL) {
		my_putstr("Stack is empty\n");
		return;
	}
	temp=first;
	while (temp != NULL) {
		print_plate(temp);
		temp=temp->next;
	}
}


// verify if the top of stack is a int_8 and print the ascii value on the std output
void print_function(struct stack *p)
{
	if (p->type == INT_8) {
		my_putchar(p->lifo.int8_lifo);
		my_putchar('\n');
	}
}

// cleaning all the stack
stack_plate free_stack(stack_plate first) {
	stack_plate temp;
	if (first == NULL) {
		return first;
	}
	while (first != NULL) {
		temp=first;
		first=first->next;
		free(temp);
	}
	return first;
}
