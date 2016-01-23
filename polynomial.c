#include "polynomial.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


//given code
struct term *make_term(int coeff, int exp) 
{
	struct term *node = malloc(sizeof(*node));
	if(node) {
		node->coeff = coeff;
		node->exp = exp;
		node->next = NULL;
	}
	return node;
}

//given code
void poly_free(polynomial *eqn)
{
	while(eqn) {
		struct term *tmp = eqn->next;
		free(eqn);
		eqn = tmp;
	}
}

//given code
void poly_print(polynomial *eqn)
{
	if(!eqn) {
		return;
	}
	if(eqn->coeff) {
		printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
		if(eqn->exp > 1) {
			printf("x^%d", eqn->exp);	
		}
		else if(eqn->exp == 1) {
			printf("x");
		}
		printf(" ");
	}
	poly_print(eqn->next);
}


char *poly_to_string(polynomial *p)
{
	//check to see if there is a polynomial p
	if(!p) {
		fprintf(stderr, "There was an error\n");
		exit(1);
	}

	char *str = malloc(sizeof(char*)*100);
	char *storage = malloc(sizeof(char*)*100);

	memset(str, '\0', sizeof(char*)*100);
	memset(storage, '\0', sizeof(char*)*100);

	size_t var = 25;

	while(p) 
	{

		storage = realloc(storage, sizeof(storage) + var); //realloc everytime through the loop

		if(p->coeff < 0) //check if coeff is negative and if so multiply by -1
		{
			p->coeff *= -1;
		}
		else
		{
			printf("%d\n", p->coeff);
		}

		if(p->coeff != 0)
		{
			if(!p->exp)
			{
				snprintf(storage, var, "%d", p->coeff); //does check and prints p->coeff to the storage array 
			}
			else
			{
				if(p->exp == 1)
				{
					snprintf(storage, var, "%dx", p->coeff);
				}
				else
				{
					snprintf(storage, var, "%dx^%d", p->coeff, p->exp);
				}
				
			}

		}


		strncat(str, storage, var); //copies storage to str array var amount(size_t)

		//checks whether to add a plu or a minus based on positive of negative
		if(p->next)
		{
			if(p->next->coeff > 0)
				strncat(str, " + ", 5);
			else
			{
				strncat(str, " - ", 5);
			}
		}
	

		var *= 2;
		p = p->next; //moves p along for the next loop
	}

	free(storage);
	return str;
}

polynomial *add_poly(polynomial *a, polynomial *b)
{
	struct term *new = NULL;
	struct term *head = NULL;
	//checks to determine where each term will go in the new polynomial
	while(a || b) 
	{
		if (a && b)
		{
			if (a->exp > b->exp)
			{
				new = make_term(a->coeff,a->exp); //creates a new position for out new polynomial
				a = a->next;
			}
			else if(a->exp < b->exp)
			{
				new = make_term(b->coeff,b->exp);
				b = b->next;
			}
			else if(a->exp == b->exp)
			{
				new = make_term((a->coeff + b->coeff), b->exp); //if the exp are equal add the coeff in new term
				a = a->next;
				b = b->next;
			}
			else
			{
				printf("Some error occured\n");
				break;
			}
		}
		else if(a)
		{
			new->next = make_term(a->coeff, a->exp);
			a = a->next;
		}

		else if(b)
		{
			new->next = make_term(b->coeff, b->exp);
			b = b->next;
		}
		else
		{
			printf("Some error occured\n");
			break;
		}

		//if head was not set by the time the loop gets here we will set it to new
		if(head == NULL)
			head = new;		

	}

	return head;
}


polynomial *sub_poly(polynomial *a, polynomial *b)
{
	struct term *new = NULL;
	struct term *head = NULL;

	//checks to determine where each term will go in the new polynomial

	while(a || b) 
	{
		if (a && b)
		{
			if (a->exp > b->exp)
			{
				new = make_term(a->coeff, a->exp); //creates a new position for out new polynomial
				a = a->next;
			}
			else if(a->exp < b->exp)
			{
				new = make_term(b->coeff,b->exp);
				b = b->next;
			}
			else if(a->exp == b->exp)
			{
				new = make_term((a->coeff - b->coeff),b->exp); //subtracts the coeffs if the exp are alike
				a = a->next;
				b = b->next;
			}
			else
			{
				printf("Some error occured\n");
				break;
			}
		}
		else if(a)
		{
			new->next = make_term(a->coeff, a->exp);
			a = a->next;
		}
		else if(b)
		{
			new->next = make_term(b->coeff, b->exp);
			b = b->next;
		}
		else
		{
			printf("Some error occured\n");
			break;
		}


		//if head was not set by the time the loop gets here we will set it to new
		if(head == NULL)
			head = new;		

	}
	return head;
}


bool is_equal(polynomial *a, polynomial *b)
{
	while(a && b) {
		if(a->coeff != b->coeff || a->exp != b->exp) //checks if the coeffs dont match or if the exp dont match
		{
			return false; //cant be equal
		}
		a = a->next;
		b = b->next;
	}


	if(a != NULL || b != NULL) //if either a or b is null then came to end of the list and it is not equal
	{
		return false;
	}

	return true;
}

void apply_to_each_term(polynomial *p, void (*transform)(struct term *))
{
	if(!p) {
		fprintf(stderr, "There was an error\n");
		exit(1);
	}

	while(p) //does loop to run through p and pass it to transom function
	{
		transform(p);
		p = p->next;
	}
}

double eval_poly(polynomial *p, double x)
{
	if(!p) {
		fprintf(stderr, "There was an error\n");
		exit(1);
	}

	double total = 0;
	while(p)
	{
		total += pow(p->coeff*x, p->exp); //multiples coeff by given x and uses pow to raise it to the power of exp
		p = p->next;
	}
	return total;
}
