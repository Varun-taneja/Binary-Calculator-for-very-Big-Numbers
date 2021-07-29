#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400
#include "operations.h"

//Token structure
typedef struct token{
	int type;
	NUMB num;
	char op;
}token;

//function declaration
token gettoken(char *expr);
