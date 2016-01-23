#include "polynomial.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

void poly_free(polynomial *eqn)
{
	while(eqn) {
		struct term *tmp = eqn->next;
		free(eqn);
		eqn = tmp;
	}
}

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
	char *str = malloc(sizeof(char*)*100);
	char *storage = malloc(sizeof(char*)*100);

	memset(str, '\0', sizeof(char*)*100);
	memset(storage, '\0', sizeof(char*)*100);

	size_t var = 25;

	while(p) 
	{
		storage = realloc(storage, sizeof(storage) + var);

		if(p->coeff < 0)
		{
			printf("negative\n");
		}

		if(p->exp > 1 && p->coeff > 1)
		{
			snprintf(storage, var, "%dx^%d", p->coeff, p->exp);
		}
		else if(p->exp == 1)
		{
			snprintf(storage, var, "%dx", p->coeff);
		}


		strncat(str, storage, var);

		if(p->next)
		{
			if(p->next->coeff > 0)
				strncat(str, " + ", 5);
		}
	

		var *= 2;
		p = p->next;
	}

	free(storage);
	return str;
}

polynomial *add_poly(polynomial *a, polynomial *b)
{
	struct term *new = NULL;
	struct term *head = NULL;
	while(a || b) 
	{
		if (a && b)
		{
			if (a->exp > b->exp)
			{
				new = make_term(a->coeff,a->exp);
				a = a->next;
			}
			else if(a->exp < b->exp)
			{
				new = make_term(b->coeff,b->exp);
				b = b->next;
			}
			else if(a->exp == b->exp)
			{
				new = make_term((a->coeff + b->coeff), b->exp);
				a = a->next;
				b = b->next;
			}
		}
		else if(a)
		{
			new->next = make_term(a->coeff, a->exp);
			//new = new->next;
			a = a->next;
		}

		else if(b)
		{
			new->next = make_term(b->coeff, b->exp);
			//new = new->next;
			b = b->next;
		}

		if(head == NULL)
			head = new;		

	}

	return head;
}


polynomial *sub_poly(polynomial *a, polynomial *b)
{
	struct term *new = NULL;
	struct term *head = NULL;
	struct term *tmp = b;

	while(b)
	{
		b->coeff *= -1;
		b = b->next;
	}
	b = tmp;

	while(a || b) 
	{
		if (a && b)
		{
			if (a->exp > b->exp)
			{
				new = make_term(a->coeff, a->exp);
				//new = new->next;
				a = a->next;
			}
			else if(a->exp < b->exp)
			{
				new = make_term(b->coeff,b->exp);
				//new = new->next;
				b = b->next;
			}
			else if(a->exp == b->exp)
			{
				new = make_term((a->coeff + b->coeff),b->exp);
				//new = new->next;
				a = a->next;
				b = b->next;
			}
		}
		else if(a)
		{
			new->next = make_term(a->coeff, a->exp);
			//new = new->next;
			a = a->next;
		}
		else if(b)
		{
			new->next = make_term(b->coeff, b->exp);
			//new = new->next;
			b = b->next;
		}

		if(head == NULL)
			head = new;		


	}

	return head;
}


bool is_equal(polynomial *a, polynomial *b)
{
	while(a && b) {
		if(a->coeff != b->coeff || a->exp != b->exp)
		{
			return false;
		}
		a = a->next;
		b = b->next;
	}


	if(a != NULL || b != NULL)
	{
		return false;
	}

	return true;
}

void apply_to_each_term(polynomial *p, void (*transform)(struct term *))
{
	while(p)
	{
		transform(p);
		p = p->next;
	}
}
