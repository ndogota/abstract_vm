// linked.h : declarations for the typed linked-list stack

#ifndef LINKED_H
#define LINKED_H

#include <stdint.h>
#include <stdlib.h>

// different type of the stack
enum list_type {
	INT_8,
	INT_16,
	INT_32,
	FLOAT,
	DOUBLE,
};

// union for making our stack multi type
union type_lifo {
	int8_t int8_lifo;
	int16_t int16_lifo;
	int32_t int32_lifo;
	float float_lifo;
	double double_lifo;
};

// structure of our stack
struct stack {
	union type_lifo lifo;
	enum list_type type;
	struct stack *next;
};
typedef struct stack *stack_plate;

// processing with stack
stack_plate get_plate();
void print_plate(struct stack *p);
int save_value(struct stack *node, double data, enum list_type type);
double get_value(stack_plate plate);

// operation
stack_plate process_operation(stack_plate first, char symbol);

// avm interpreter functions
stack_plate push_function(stack_plate first, double data, enum list_type type);
stack_plate pop_function(stack_plate first);
stack_plate add_function(stack_plate first);
stack_plate sub_function(stack_plate first);
stack_plate mul_function(stack_plate first);
stack_plate div_function(stack_plate first);
stack_plate mod_function(stack_plate first);
int assert_function(stack_plate first, double value);
void dump_function(stack_plate first);
void print_function(struct stack *p);

// cleaning functions
stack_plate free_stack(stack_plate first);

#endif
