#include "list.h"


// Number stack:
typedef struct node_num {
	number *a;
	struct node_num *prev;
}node_num;

typedef node_num *stack_num;

// Function declaration - Number stack:
void init_num(stack_num *s);
void push_num(stack_num *s, number *a);
NUMB pop_num(stack_num *s);
int isempty_num(stack_num *s);



/*--------------------------------------------------------------------------------------------------------------------------------------*/



// Character stack:
typedef struct node_ch {
	char a;
	struct node_ch *prev;
}node_ch;

typedef node_ch *stack_ch;

// Function declaration - Character stack
void init_ch(stack_ch *s);
void push_ch(stack_ch *s, char t);
char pop_ch(stack_ch *s);
int isempty_ch(stack_ch *s);
char top_ch(stack_ch *sch);

