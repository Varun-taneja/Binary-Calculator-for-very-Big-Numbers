#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <string.h>
#include"token.h"


int precedance(char prec) { //while we push and pop from operator stack, we need to follow rules of precedence in infix evaluation
	switch(prec) {
		case ')' :
			return 0;
			break;
		case '+' : case '-' :
			return 1;
			break;
		case '*' : case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
		case '(' :
			return 4;
			break;
		default :
			return 5;
			break;
	}
}
number *infix(char *exp) {  //evaluation of infix
	token t;
	char curr_op, prev_op, ch; //op here means operator
	int cnt_ob = 0, cnt_cb = 0, curr, prev;
	NUMB n1, n2, n12; //n1 & n2 - two numbers and n12 is formed after performing some operation on those two
	n1 = (NUMB)malloc(sizeof(number));
	n2 = (NUMB)malloc(sizeof(number));
	n12 = (NUMB)malloc(sizeof(number));
	initNo(n1);
	initNo(n2);
	initNo(n12);
	stack_num snum;
	stack_ch sch;
	init_num(&snum);
	init_ch(&sch);
	prev = ERR;
	while(1) {
		t = gettoken(exp); //calling the gettoken function (called again and again for tokens)
		curr = t.type;
		if(curr == prev && prev == OPERAND) {
			return NULL;
		}
		if(t.type == OPERAND){
			push_num(&snum, t.num); //push the token number into the number stack
        }
		else if(t.type == OPERATOR){
			curr_op = t.op;     // current operator = the token operator
			if(curr_op == '(')  //have to keep the count of open (ob) and closed(cb) brackets
				cnt_ob++;
			if(curr_op == ')')
				cnt_cb++;
			if(cnt_cb > cnt_ob) //error if there are more closed brackets than open
				return NULL;
			if(!isempty_ch(&sch)) {
				prev_op = top_ch(&sch); //prev op is the one at the top of stack
				while(precedance(prev_op) >= precedance(curr_op)) { //precedence of operator has to be seen before pushing it in the stack
					prev_op = pop_ch(&sch); //top of stack popped if its precedence is higher
					if(!isempty_num(&snum)) { //operator popped has to be used with two numbers
						n1 = pop_num(&snum);
					}
					else{
						push_ch(&sch, prev_op);
						break;
					}
					if(!isempty_num(&snum)) { //if two numbers are there in the number stack, we go forward with the operation
						n2 = pop_num(&snum);
					}
					else {
						push_ch(&sch, prev_op);
						push_num(&snum, n1);
						break;
					}
					if((prev_op == '/') && n1 == 0) { // a number cannot be divided by 0
                        printf("Mathematical error\n");
                        return NULL;
                    }
					switch (prev_op) { //operation performed according to the previous operator
						case '+' :
							n12 = add(n2, n1);
							push_num(&snum, n12);
							break;
						case '-' :
							n12 = sub(n2, n1);
							push_num(&snum, n12);
							break;
						case '*' :
							n12 = mult(n2, n1);
							push_num(&snum, n12);
							break;
						case '/' :
							n12 = division(n2, n1);
							push_num(&snum, n12);
							break;
						case '(' : //no operation performed, have to wait till we encounter ')'
							push_ch(&sch, prev_op);
							push_num(&snum, n2);
							push_num(&snum, n1);
							break;
							return NULL;
					}
					if (prev_op == '(')
						break;
					if(!isempty_ch(&sch))
						prev_op = top_ch(&sch);
					else
						break;
				}
			}
			push_ch(&sch, t.op);
			if(curr_op == ')') {  // everything inside ( ) is operated
				ch = pop_ch(&sch); //both of them will be popped out therefore reducing the count
				cnt_cb--;
				ch = pop_ch(&sch);
				cnt_ob--;
			}
		}
		else if(t.type == END) { //reached end of character therefore the expression has to be evaluated
			if(cnt_ob == cnt_cb) {
				while(!isempty_ch(&sch)) { //until all operations are done
					if(!isempty_num(&snum)) {
						n1 = pop_num(&snum);
					}
					else {
						printf("Less operands\n"); //there is a lack of operands ie 1 out of 2 is there
                        return NULL;
					}
					if(!isempty_num(&snum)) { //an operation requires 2 numbers
						n2 = pop_num(&snum);
					}
					else {
						fprintf(stderr, "Less operands\n");
                        return NULL;
					}
					ch = pop_ch(&sch); //now perform operation on the two numbers
					if((ch == '/') && n1 == 0) {
						fprintf(stderr, "Mathematical error\n");
						return NULL;
					}
					switch(ch) { //now perform the operation
						case '+' :
							n12 = add(n2, n1);
							push_num(&snum, n12);
							break;
						case '-' :
							n12 = sub(n2, n1);
							push_num(&snum, n12);
							break;
						case '*' :
							n12 = mult(n2, n1);
							push_num(&snum, n12);
							break;
						case '/' :
							n12 = division(n2, n1);
							push_num(&snum, n12);
							break;
						default :
							return NULL;
					}
				}
			}
			else { //if operation cant be performed there is an error in input therefore
				fprintf(stderr, "Error in input\n");
				return NULL;
			}
			if(!isempty_num(&snum)){
				n12 = pop_num(&snum);
				if(isempty_num(&snum))
					return n12; //after all operations only 1 number will be left
				else {
                    fprintf(stderr, "Operators are lacking\n");
                    return NULL; //if more that one number remains if there are less operators
                }
			}
			else {
				fprintf(stderr, "Operands are lacking\n"); //if numbers are less and operators are more
				return NULL;
			}
		}
		else if(t.type == ERR) { //if token returns an error than nothing can be returned
			return NULL;
		}
		prev = curr; //continue the while loop
	}
}

