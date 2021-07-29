#define PLUS 1
#define MINUS -1


//Node structure:
typedef struct node {
	int num;
	struct node *next, *prev;
}node;

typedef node* NODE; //pointer to node can be called as NODE


//Number structure:
typedef struct number {
	int sign, dec; // sign for - and + of numbers , dec for storing no. of decimal places in the number
	node *h, *t; //head & tail
}number;

typedef number* NUMB; // pointer to number can be called as NUMB


//Function declaration - list:
void initNo(number *numb);
void append(number *numb, char ch);
void traverse(number numb);
void appendleft(number *numb, int no);
int length(number numb);
void remov(number *numb, int pos);
void Exzero_out(number *numb);











