#ifndef FUNCTIONS_FOR_MAIN
#define FUNCTIONS_FOR_MAIN

#include <fstream>
#include "my_stack.h"
#define SIZE_OF_FILE_BUFFER 256

void delete_even(my_stack &obj) {
	int col = obj.top_return();
	for (int i = 0; i <  col / 2 + 1; i++) {
		obj - (2+i);
	}
}

my_stack *read_from_files(char *files[], int count) {
	my_stack *tmp = NULL;

	try {
		tmp = new my_stack[count-1];
	}
	catch (bad_alloc ba) {
		cerr << "Error:can`t allocate memory!\n";
		return NULL;
	}

	char buffer[SIZE_OF_FILE_BUFFER];
	
	for (int i = 1; i < count; i++) {
		ifstream inputFile(files[i], ios::in);
		
		if (!inputFile) {
			cerr << "Error:can`t open file!\n";
			delete[] tmp;
			return NULL;
		}

		while (inputFile.getline(buffer, sizeof buffer)) {
			try {
				tmp[i - 1].push(buffer);
			}
			catch (bad_alloc ba) {
				inputFile.close();
				delete[] tmp;
				return NULL;
			}
		}
		inputFile.close();
	}

	return tmp;
}

void show_stacks(my_stack *ptr, int size_of_array) {
	for(int i = 0 ; i < size_of_array ; i++) {
		ptr[i].show();
		cout << endl;
	}
}


#endif