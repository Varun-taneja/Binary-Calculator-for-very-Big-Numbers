#include <stdio.h>
#include <stdlib.h>
#include "stack_num_ch.h"


//Functions to be performed on the stack storing numbers.

//initialize the num stack
void init_num(stack_num *s) {
	*s = NULL;  //making sure theres no dangling pointer
}

//add numbers and to the num stack
void push_num (stack_num *s, number *n) {
	stack_num p;  //p is like a newnode
	p = (node_num *)malloc(sizeof(node_num));
	p->a = n;
	p->prev = *s;
	*s = p;
}

// remove the top number in the num stack and return it
number *pop_num(stack_num *s) {
	number *n;
	stack_num p; //pointing to top
	n = (*s)->a;
	p = *s;
	*s = (*s)->prev;
	free(p);
	return n;
}

//check if the num stack is empty
int isempty_num (stack_num *s) {
	return *s == NULL;
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//  Stack implementation to store character Operators.
void init_ch(stack_ch *s) {
	*s = NULL;
}
void push_ch (stack_ch *s, char t) {
	stack_ch p;
	p = (node_ch *)malloc(sizeof(node_ch));
	p->a = t;
	p->prev = (*s);
	*s = p;
}
char pop_ch(stack_ch *s) {
	char t;
	stack_ch p;
	p = (*s);
	t = (*s)->a;
	*s = (*s)->prev;
	free(p);
	return t;
}
int isempty_ch (stack_ch *s) {
	return *s == NULL;
}

char top_ch(stack_ch *sch) {
	char ch;
	ch = pop_ch(sch);
	push_ch(sch, ch);
	return ch;
}



