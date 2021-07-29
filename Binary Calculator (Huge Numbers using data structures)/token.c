#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <string.h>
#include"token.h"




enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC }; //assigning names to constants

token gettoken(char *expr) { //the expression we type goes here
	static int i = 0;  //remains in memory during runtime
	NUMB n = (NUMB)malloc(sizeof(number)); //dynamic memory allocation
	initNo(n);
	char currchar;
	static enum state currstate = SPC; //initialized state because its the most suitable
	enum state nextstate;
	token t;

	while(1) {   //while we break from while
		currchar = expr[i]; //evaluating individual characters of the expression
		switch(currstate) {
			case NUMBER: //if cureent state is a NUMBER
				switch(currchar) { //character to be evaluated next
					case '0':case '1':case '2': case '3': case '4':case '5':case '6': case '7': case '8':case '9': //if its a digit, number continues
						nextstate = NUMBER;
						append(n, currchar); //adding it to the end of the number
						i++; //next character
						break;

					case '+': case '-': case '*': case '/': case '(': case ')': //if its an operator
						nextstate = OP;
						t.type = OPERAND; //the token returned is an operand type  (before operator)
						t.num = n;
						currstate = nextstate;
						i++;
						return t; //return the token
						break;

					case '\0': //end of line
						nextstate = FINISH;
						t.type = OPERAND; //return the operant type token
						t.num = n;
						currstate = nextstate;
						return t;
						break;

					case ' ': //space
						nextstate = SPC;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						i++;
						return t; //return the number token (operand)
						break;

					case '.': //decimal point
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default: //other than the above ones, we get an error
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case DOT: //encountering a decimal point
				switch(currchar) {
					case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':case '9':
						append(n, currchar);
						n->dec++;
						nextstate = DOT; //still in dot(decimal state)
						currstate = nextstate;
						i++;
						break;

					case '+': case '-': case '*': case '/': case '(': case ')':
						nextstate = OP;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						return t;
						break;

					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						i++;
						return t;
						break;

					default: //other than the above ones, we get an error
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case OP: //encountering an operator
				switch(currchar) {
					case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
						t.type = OPERATOR;
						t.op = expr[i - 1]; //as current expression's element has gone one step ahead
						nextstate = NUMBER;
						currstate = nextstate;
						return t; //return the operator token
						break;

					case '+': case '-': case '*': case '/': case '(': case ')':
						nextstate = OP;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;

					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						t.type = OPERATOR;
						t.op = expr[i -1];
						currstate = nextstate;
						i++;
						return t;
						break;

					default: //
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH: //encounters \0
				t.type = END;
				return t;
				break;

			case ERROR: //anything other than whats defined
				t.type = ERR;
				return t;
				break;

			case SPC: //encounters a space
				switch(currchar) {
					case '0': case '1': case '2': case '3': case '4':case '5': case '6': case '7': case '8': case '9':
						append(n, currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '!': case '(': case ')':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;
					case '.':
						nextstate = DOT;
						i++;
						break;

					default: // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}
