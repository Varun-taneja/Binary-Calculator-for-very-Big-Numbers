#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "operations.h"


//Function to equal the digits after decimal point
void DecLenEqual(NUMB num1, NUMB num2) {
	int i;
	int diff = num1->dec - num2->dec;  //calculate difference between the no. of digits after decimal point between the two numbers

	if(diff > 0) { // if 2nd no. has lesser decimal places
		for(i = 0; i < diff; i++) {  //add extra zeroes to num2
			append(num2, '0');
			num2->dec++;
		}
	}

	else if(diff < 0) { // if 2nd no. has more decimal places
		diff = -1*diff;
		for(i = 0; i < diff; i++) {  //add extra zeroes to num1
			append(num1, '0');
			num1->dec++;
		}
	}
}

//Adding zeroes to the start of the smaller number therefore making length of both equal.
void NumLenEqual(NUMB num1, NUMB num2) {
	int differ = length(*num1) - length(*num2); //calc difference of length
    int i = 0;
	if(differ > 0) { //if num1's length is greater
		while(i < differ) {
			appendleft(num2, 0);   //adding 0's at the start
			i++;
		}
		return;
	}
	else if(differ < 0) { //if num2's length is greater
		differ = -1*differ;
		while(i < differ) {
			appendleft(num1, 0);  //adding 0's at the start
			i++;
		}
		return;
	}
	return;
}

//Determines if a number is 0 or not, if it is then returns 0
int IsZero(number numb) {
	int i, ifzero = 0;
	NODE p = numb.h;
	for(i = 0; i < length(numb); i++) { //traversing the whole number
		if(p->num != 0)       //even if one digit isn't zero, it returns 1;
			ifzero = 1;
		 p = p->next;
	}
	return ifzero;
}

// If length is equal,find the greater of the two numbers;
int TwoNumEqual(number num1, number num2) {
	NumLenEqual(&num1, &num2);   //adding zeroes at the start
	DecLenEqual(&num1, &num2);   //adding zeroes to make decimal length equal
	NODE p, q;
	int len;
	int i;
	len = length(num1);
	p = num1.h;
	q = num2.h;
	for(i = 1; i <= len; i++) {
		if(p->num > q->num)
			return 1;  // num1 greater than num2
		else if(p->num < q->num)
			return -1;  //num1 is less than num2
		p = p->next;
		q = q->next;
	}
	return 0;    //num1 = num2
}

//Addition Operation
NUMB add(NUMB num1, NUMB num2) {
	NUMB result;
	result = (NUMB)malloc(sizeof(number));
	initNo(result);
	DecLenEqual(num1, num2);  //making decimal places length equal
	NumLenEqual(num1, num2);  ////making overall length equal
	if(num1->sign != num2->sign) {  //if signs are different
		if(num1->sign == MINUS) { // -num1 + num2
			num1->sign = PLUS;
			result = sub(num2, num1); //ie num2 - num1
		}
		else if(num2->sign == MINUS) { // num1 + -num2
			num2->sign = PLUS;
			result = sub(num1, num2); //ie num1 - num2
		}
	}
	else if(num1->sign == num2->sign) { //signs are same
		int i, n1, n2, carry = 0, sum;
		int len_num1, len_num2;
		node *t1 = num1->t;   //points to the last digir
		node *t2 = num2->t;
		len_num1 = length(*num1);
		if(num1->sign == MINUS) //signs of both nums are -ve
			result->sign = MINUS;
		else
			result->sign = PLUS;
        for(i = 1; i <= len_num1; i++) { //addition starts from right hence tails are used , goes on until all digits in num1 are exhausted
            n1 = t1->num; //pointing to the digit stored in the node
            n2 = t2->num;
            sum = n1 + n2 + carry;
            carry = sum / 10;
            sum = sum % 10;
            appendleft(result, sum); //adding digits (nodes) to start of result to finally make a number
            t1 = t1->prev;  //point to the previous node ie making it behave as tail
            t2 = t2->prev;
        }
		result->dec = num1->dec; //final result will always have same no of decimal places as either number as we had made both equal
		if(carry != 0)  //for an outstanding carry after digits of the greater number have been exhausted
			appendleft(result, carry);
	}
	return result;
}



//Substraction operation.
NUMB sub(NUMB num1, NUMB num2) {
	NUMB result;
	result = (NUMB)malloc(sizeof(number));
	initNo(result);

	DecLenEqual(num1, num2); //making the decimal digits length equal (0's at end)
	NumLenEqual(num1, num2); //making the overall length equal (0's at start)
	if(num1->sign != num2->sign) { //if signs are equal we add keeping individual signs in mind
		if(num1->sign == MINUS) {
			num1->sign = PLUS;  //-num1 - num2
			result = add(num1, num2);
			result->sign = MINUS; //
		}
		else if(num2->sign == MINUS) {
			num2->sign = PLUS;   // num1 - -num2
			result = add(num1, num2);
			result->sign = PLUS;
		}
	}
	else if(num1->sign == num2->sign) { //if signs are equal we subtract keeping individual signs in mind
		if(num1->sign == MINUS) {
			num1->sign = num2->sign = PLUS; // -num1 - -num2
			result = sub(num2, num1);
		}
		else if(num1->sign == PLUS) { //num1 - num2
			int n1, n2, diff, borrow = 0, i, len;
			NODE t1 = num1->t; // pointing to tail because subtraction also starts from the left
			NODE t2 = num2->t;

			len = length(*num2); //as length of both numbers is same now
			if(TwoNumEqual(*num1, *num2) == 1) { //if num1 > num2
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n1 = n1 - borrow;
					if(n1 >= n2) {
						diff = n1 - n2;
						borrow = 0;  //eg 9 - 8 , diff = 1 , borrow = 0
						appendleft(result, diff); //adding digits at the start of result number
					}
					else {
						n1 = n1 + 10; //takes in borrow from digit to the left
						diff = n1 - n2;
						borrow = 1;
						appendleft(result, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(TwoNumEqual(*num1, *num2) == -1) { //if num2 > num1
				result->sign = MINUS; //as num1 - num2 will result in a negative ans
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						appendleft(result, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						appendleft(result, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else {       //if both numbers are exactly equal
				if(TwoNumEqual(*num1, *num2) == 0) {
					appendleft(result, 0); //result is a 0
				}
			}
		}
	}
	result->dec = num1->dec; //overall decimal places is equal to either umber as we had made those equal
	return result;
}

//Multiplication Operation.
NUMB mult(NUMB num1, NUMB num2) {
	NUMB result = (NUMB)malloc(sizeof(number));
	initNo(result);

	if((IsZero(*num1) == 0) || (IsZero(*num2) == 0)) { //if either number is 0, reult is automatically 0
		append(result, '0');
		return result;
	}
	int lengthdiff;
	if(num1->sign == num2->sign) { //if signs are same , results sign is +ve
		result->sign = PLUS;
		num1->sign = num2->sign = PLUS;
	}
	else {                         //otherwise -ve
		result->sign = MINUS;
		num1->sign = num2->sign = PLUS;
	}
	lengthdiff = length(*num1) - length(*num2); //check which number has greater no. of digits and put that as the 1st number
	if(lengthdiff < 0) {
		result = mult(num2, num1);
		return result;
	}
	else {
		NODE t1, t2; //tails of respective numbers

		int len_num1 = length(*num1);
		int len_num2 = length(*num2);
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_num1]; //maximum number of digits the result can have ie 2*larger_number

		for(i = 0; i < 2 *len_num1; i++) //making the result have an array containing 0's
			tempresult[i] = 0;

		int k = 2 * len_num1 - 1;

		t2 = num2->t; //tail

		for(i = 0; i < len_num2; i++) { //the whole num1 digits have to be multiplied by
			t1 = num1->t;
			int carry1 = 0, carry2 = 0; //carry1 is for multiplication of digits , carry2 is for the addition we do

			for(j = k - i; j > len_num1 - 2; j--) { //start from last digit of greater num
				if(t1 != NULL && t2 != NULL) {
					n1 = t1->num * t2->num + carry1;
					t1 = t1->prev;
					carry1 = n1 / 10;
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + carry2; //add digits to the result array created
					carry2 = n2 / 10;
					n2 = n2 % 10;
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}
			tempresult[j] = carry1 + carry2 + tempresult[j];
			len_num1--;
			t2 = t2->prev;
		}
		for(i= k; i >= len_num1 - 1 && i >= 0; i--) { //keep on adding the digits in rhe array to nodes and make a number
			appendleft(result, tempresult[i]);
		}
		result->dec = num1->dec + num2->dec; //as decimal places get added after miltiplying
		return result;
	}
}

//Division Operation.
number *division(NUMB num1, NUMB num2){
	if(IsZero(*num2) == 0) { //cannot divide a number by 0
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}
	Exzero_out(num1); //removing the extra 0's
	Exzero_out(num2);

	int k = num1->dec > num2->dec ? num1->dec : num2->dec; //k = no of greater of the two decimal places
	int i = 0;

	while(i < k) { //removing all decimal places and making the numbers  whole numbers for division
		if(num1->dec > 0)
			num1->dec--;
		else
			append(num1, '0');
		if(num2->dec > 0)
			num2->dec--;
		else
			append(num2, '0');
		i++;
	}
	i = 9; //maximum number the divisor can be multiplied with to do part subtraction that leads to the final ans

	NUMB i_val, divi_part, result, quo, prod;
	i_val = (NUMB)malloc(sizeof(number));
	divi_part = (NUMB)malloc(sizeof(number));
	result = (NUMB)malloc(sizeof(number));
	prod = (NUMB)malloc(sizeof(number));
	quo = (NUMB)malloc(sizeof(number));

	initNo(result);
	initNo(i_val);
	initNo(quo);
	initNo(divi_part);

	if(num1->sign == num2->sign) { //if signs are equal, quotients sign is +ve
		quo->sign = PLUS;
		num1->sign = num2->sign = PLUS;
	}
	else { //otherwise sign is -ve
		quo->sign = MINUS;
		num1->sign = num2->sign = PLUS;
	}
	NODE p = num1->h; //num1 is the dividend
	char ch = p->num + '0'; //taking individual character(digit) from num1 and comparing with num2
	append(divi_part, ch); //appending those digits to form a number

	while(quo->dec < DECIMALPLACES){ //DECIMALPLACES is the maximum number of decimal places we want to calculate for the quotient
		while(i >= 0){
			appendleft(i_val, i); //number with which the divisor(num2) is multiplied for div part subtraction
			prod = mult(num2, i_val);
			result = sub(divi_part, prod); //part dividend - product of i and num2
			if(result->sign != MINUS) { //if part dividend is greater than prod
				append(quo, i + '0'); //add digit to quotient
				NODE tmp = i_val->h; //refreshing i_val for the next i value
				free(tmp);
				i_val->h = i_val->t = NULL;
				break;
			}
			else{
				NODE tmp = i_val->h;
				free(tmp);
				i_val->h = i_val->t = NULL;
				i--; //decreasing i and trying with the other number
			}
		}
		divi_part  = result;

		if(p->next != NULL) { //combining the next dividend digit to part dividend for subtraction
			p = p->next;
			ch = p->num + '0';
			append(divi_part, ch);
		}
		else{ //if none left, adding a decimal point and add 0
			quo->dec++;
			append(divi_part, '0');
		}
		i = 9; //
		NODE tmp = i_val->h;
		free(tmp);
		i_val->h = i_val->t = NULL;
	}
	quo->dec--; //it adds a decimal place so we have to remove it
	return quo;
}



