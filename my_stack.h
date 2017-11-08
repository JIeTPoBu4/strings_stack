#ifndef _MY_STACK_H
#define _MY_STACK_H

#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

class my_stack {
	char **strings;
	int top;
	int size;
	char **create_strings(int count);
	void delete_strings(char ***str, int count);
	void copy_strings(char **str_out, char **str_in, int count);
public:
	my_stack() {
		strings = NULL;
		top = size = -1;
	}
	my_stack(const my_stack &obj);
	my_stack(int count);
	~my_stack() {
		delete_strings(&strings, top + 1);
	}

	void push(const char *str);
	const char *pop();
	int top_return() {
		return top;
	}

	void show();

	my_stack operator+(const char *str);
	my_stack operator-(int num);
	my_stack operator=(const my_stack &obj);
	friend ostream &operator<<(ostream &stream, my_stack &obj);
	friend istream &operator>>(istream &streaam, my_stack &obj);
};

#endif