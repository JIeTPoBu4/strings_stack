#ifndef _FUNCTIONS_FOR_MAIN_H
#define _FUNCTIONS_FOR_MAIN_H

#include "my_stack.h"

void delete_even(my_stack &obj);
my_stack *read_from_files(char *files[], int count);
void show_stacks(my_stack *ptr, int size_of_array);

#endif