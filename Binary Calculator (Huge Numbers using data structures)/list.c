#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//initializing the number
void initNo(NUMB numb) {
	numb->h = numb->t = NULL;
	numb->dec = 0;
	numb->sign = PLUS;
}

//Adding digits at the end (node) of the number
void append(NUMB numb, char ch) {
	if(ch < '0' || ch > '9') //digit to be added
		return;
	NODE p = (NODE)malloc(sizeof(node)); //dynamically allocated memory
	if(p == NULL) //if memory has not been allocated
		return;
	p->num = ch - '0'; //digit value
	p->next = NULL;
	if((numb->h == NULL) && (numb->t == NULL)) { //empty number
		p->prev = NULL;
		numb->h = p;
		numb->t = p;
		return;
	}
	p->prev = numb->t; //adding when nodes already exist
	numb->t->next = p;
	numb->t = p;
	return;
}


//calculate the length of the number
int length(number numb) {
	NODE p;
       	p = numb.h;
	int count = 0;
	while(p != NULL) { //while there are nodes left to traverse
		count++;
		p = p->next;
	}
	return count;
}

//adding digit to the left of a number (node)
void appendleft(NUMB numb, int no) {
	if(no < 0 || no > 9) // 0 <= no <=9
		return;
	NODE p = (NODE)malloc(sizeof(node));
	if(!p)
		return;
	p->num = no;
	p->prev = NULL;
	if((numb->h == NULL) && (numb->t == NULL)){ //empty list (no nodes having digits)
		p->next = NULL;
		numb->h = numb->t = p;
		return;
	}
	p->next = numb->h; //adding when nodes with digits already exist
	numb->h->prev = p;
	numb->h = p;
	return;
}

//deleting digits at a certain position
void remov(NUMB numb, int pos){
	int i;
	NODE p, tmp;

	if(pos < 0 || pos >= length(*numb)) // error position input
		return;

	p = numb->h;

	for(i = 0; i < pos - 1; i++) //go to the node just before the position to be deleted
		p = p->next;

	if(numb->h == NULL) { //empty number
		return;
	}
	else if(length(*numb) == 1) { //contains only one position
		numb->h = numb->t = p = NULL;
		return;
	}
	else if(pos == 0) { //removing the first element
		p->next->prev = NULL;
		numb->h = p->next;
		free(numb);
		return;
	}
	else if(pos == length(*numb) - 1) { //last digit removing
		tmp = p->next;
		p->next = NULL;
		numb->t = p;
		free(tmp);
		return;
	}
	tmp = p->next;
	p->next = p->next->next;
	tmp->next->prev = p;
	free(tmp);
	return;
}



//removed extra 0's from the start and the end (decimal) of the number
void Exzero_out(NUMB numb) {
	NODE p = numb->h; //pointing at the start
	int i, len = length(*numb);
	for(i = 0; i < len - numb->dec -1; i++) { //remove zeroes from start
		if(p->num == 0) {  //while the num in the node is 0
			numb->h = p->next;
			p->next = NULL;
			numb->h->prev = NULL;
			free(p);
			p = numb->h;
		}
		else {
			break;
		}
	}
	p = numb->t;
	int decimal = numb->dec;
	for(i = 0; i < decimal - 1; i++) { //until the decimal places are over, we start from the left
		if(p->num == 0) {
			numb->t = p->prev;
			p->prev = NULL;
			numb->t->next = NULL;
			free(p);
			p = numb->t;
			numb->dec--;

		}else {
			break;
		}
	}
	return;
}

//print the number stored (without the extra zeroes)
void traverse(number numb) {
	NODE p;
	int pos = 0;
	Exzero_out(&numb);
	p = numb.h;
	if(numb.sign == MINUS) { //if sign is minus
		printf("-");
		numb.sign = PLUS;
	}
	while(p != NULL) {
		pos++;
		if(pos == (length(numb) - numb.dec + 1)) //decimal point to be printed
			printf(".");
		printf("%d", p->num);
		p = p->next;
	}
	printf("\n");
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/
