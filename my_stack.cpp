#ifndef _MY_STACK
#define _MY_STACK

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <new>
#include "my_stack.h"

#define COUNT_OF_STRINGS 1
#define SIZE_OF_BUFFER 1000

using namespace std;

char **my_stack::create_strings(int count) {
	char **temp = NULL;
	try{
		temp = new char *[count];
		
		for (int i = 0; i < count; i++) {
			temp[i] = NULL;
		}
	}
	catch (bad_alloc ba){
		cerr << "Error:can`t allocate memory!\n";
		throw;
	}
	
	return temp;
}

void my_stack::delete_strings(char ***str, int count) {
	if (*str) {
		for (int i = 0; i < count ; i++) {
			delete[] (*str)[i];
		}
		delete[] (*str);
	}
	*str = NULL;
}

void my_stack::copy_strings(char **str_out, char **str_in, int count) {
	for (int i = 0; i < count; i++) {
		try {
			str_out[i] = new char[strlen(str_in[i]) + 1];
		}
		catch (bad_alloc ba) {
			delete_strings(&str_out, i);
			delete_strings(&str_in, count);
			throw;
		}
		strncpy(str_out[i], str_in[i], strlen(str_in[i]) + 1);
	}
}
//std::string, std::copy()
my_stack::my_stack(const my_stack &obj) {
	strings = create_strings(obj.size);
	copy_strings(strings, obj.strings, obj.top + 1);
	size = obj.size;
	top = obj.top;
}

void my_stack::push(const char *str) {
	if (!strings) {
		strings = create_strings(COUNT_OF_STRINGS);
		size = COUNT_OF_STRINGS;
		try {
			strings[0] = new char[strlen(str) + 1];
		}
		catch (bad_alloc ba) {
			cerr << "Error:can`t allocate memory!\n";
			throw;
		}
		strncpy(strings[0], str, strlen(str) + 1);
		top = 0;
	}
	else {
		if (top == (size-1)) {
			char **buffer = NULL;
			try{
				buffer = create_strings(size);
			}
			catch (bad_alloc) {
				cerr << "Error:can`t allocate memory!\n";
				delete_strings(&strings, size);
				throw;
			}

			copy_strings(buffer, strings, size);
			delete_strings(&strings, size);

			try{
				strings = create_strings(size * 2);
			}
			catch (bad_alloc ba) {
				cerr << "Error:can`t allocate memory!\n";
				delete_strings(&buffer, size);
				throw;
			}

			copy_strings(strings, buffer, size);
			delete_strings(&buffer, size);
			try{
				strings[size] = new char[strlen(str) + 1];
			}
			catch (bad_alloc ba) {
				cerr << "Error:can`t alloc memory!\n";
				delete_strings(&strings, size);
				throw;
			}

			strncpy(strings[size], str, strlen(str) + 1);
			top = size;
			size *= 2;
			}
		else{

			try{
				strings[top + 1] = new char[strlen(str) + 1];
			}
			catch (bad_alloc ba) {
				cerr << "Error:can`t allocate memory!\n";
				delete_strings(&strings, size);
				throw;
			}

			strncpy(strings[top + 1], str, strlen(str) + 1);
			top++;
		}
	}
}

const char *my_stack::pop() {
	if (top == -1) {
		cerr << "Error:stack is empty!\n";
		char *temp = NULL;
		try{
			temp = new char[1];
		}
		catch (bad_alloc ba) {
			cerr << "Error:can`t allocate memory!\n";
			throw;
		}

		temp[0] = '\0';
		return temp;
	}

    char *out_buffer = NULL;

	try{
		out_buffer = new char[strlen(strings[top]) + 1];
	}
	catch (bad_alloc ba) {
		cerr << "Error:can`t allocate memory!\n";
		delete_strings(&strings, top + 1);
		throw;
	}

	strncpy(out_buffer, strings[top], strlen(strings[top]) + 1);
	delete[] strings[top];
	strings[top] = NULL;
	top--;

	return out_buffer;
}

ostream &operator<<(ostream &stream, my_stack &obj) {
	const char *temp = obj.pop();
	char *buffer = new char[strlen(temp) + 1];
	strcpy(buffer, temp);
	delete[] temp;
	stream << buffer;
	delete[] buffer;
	return stream;
}

istream &operator>>(istream &stream, my_stack &obj) {
	char buffer[SIZE_OF_BUFFER];
	stream >> buffer;
	buffer[SIZE_OF_BUFFER-1] = '\0';
	obj.push(buffer);
	return stream;
}

my_stack my_stack::operator+(const char *str) {
	push(str);
	return *this;
}

my_stack my_stack::operator=(const my_stack &obj) {
	delete_strings(&strings, top + 1);
	strings = create_strings(obj.size);
	copy_strings(strings, obj.strings, obj.top + 1);
	size = obj.size;
	top = obj.top;
	return *this;
}

my_stack my_stack::operator-(int num) {
	if (top + 1  < num || num < 0 ) {
		return *this;
	}

	int ptr = top;

	while (num != 1) {
		ptr--;
		num--;
	}

	delete[] strings[ptr];

	for (int i = ptr; i < top; i++) {
		strings[i] = strings[i + 1];
	}

	top--;
	return *this;
}

void my_stack::show() {
	if(top == -1) {
		cout << "Stack is empty!\n";
		return;
	}
	
	for(int counter = top ; counter >= 0; counter--) {
		cout << strings[counter] << endl;
	}
}

#endif
