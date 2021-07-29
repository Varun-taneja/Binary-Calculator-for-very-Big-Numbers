#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define Y 1
#define N 0

int main(){

    printf("--Binary Number Calculator, DSA MINI PROJECT (BC)--\n");
    printf("||Varun Taneja , 111903158 , Div 2, S4 Batch||\n\n");
    printf("The operations that can be performed are '+' '-' '/' '*'.\n");
    printf("We can use decimal numbers, preferably put spaces between each character and '(' and ')' can also be used.\n");
    printf("This calculator will run only once.\nEnter your expression now: \n");

    NUMB result;
    result = (NUMB)malloc(sizeof(number));
    initNo(result);

    char expression[2000];
    gets(expression);
    result = infix(expression);
    traverse(*result);
    return 0;
}


