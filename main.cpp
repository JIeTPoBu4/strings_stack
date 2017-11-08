#include "my_stack.h"

#include <iostream>
#include "functions_for_main.h"

using namespace std;


int main(int argc, char *argv[]) {
	if(argc == 1) {
		cerr << "No input file!\n";
		return 1;
	}

	try{
		my_stack *array_of_stacks = read_from_files(argv, argc);

		if(!array_of_stacks) {
			return 1;
		}
		
		cout << "Before delete:\n";
		show_stacks(array_of_stacks, argc - 1);

		for(int i=0 ; i < argc - 1 ; i++) {
			delete_even(array_of_stacks[i]);
		}

		cout << "\nAfter delete:\n";
		show_stacks(array_of_stacks, argc - 1);

		delete[] array_of_stacks;
	}
	catch(bad_alloc ba) {
		return 1;
	}

	return 0;
}
