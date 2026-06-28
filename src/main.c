// main.c : entry point, forwards the command line arguments to the interpreter

#include "../include/main.h"

int main(int argc, char **argv)
{
    process_arg(argc, argv);
    return 0;
}