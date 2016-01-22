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

	size_t var = 50;

	while(p) {;
		printf("exp: %d\n", p->exp);
		printf("coeff: %d\n", p->coeff);

		if(p->coeff)
		{
			if (p->coeff > 1)


			var += strlen(storage);
			strncat(str, storage, var);


		}
		p = p->next;

	}

	free(storage);
	return str;
}

polynomial *add_poly(polynomial *a, polynomial *b)
{
	struct term *new = make_term(0, 0);
	struct term *head = new;

	while(a || b) 
	{
		//printf("A: %d B: %d\n", a->exp, b->exp);
		if (a && b)
		{
			printf("A: %d B: %d\n", a->exp, b->exp);
			if (a->exp > b->exp)
			{
				new->coeff = a->coeff;
				new->exp = a->exp;
				new->next = make_term(0,0);
				new = new->next;
				printf("%d\n", a->exp);
				a = a->next;
			}
			else if(a->exp < b->exp)
			{
				new->coeff = b->coeff;
				new->exp = b->exp;
				new->next = make_term(0,0);
				new = new->next;
				printf("if 2\n");
				b = b->next;
			}
			else if(a->exp == b->exp)
			{
				printf("here\n");
				new->coeff = a->coeff + b->coeff;
				new->exp = b->exp; 
				new->next = make_term(0,0);
				new = new->next;
				printf("if 3\n");
				a = a->next;
				b = b->next;
			}
		}
		else if(a)
		{
			new->next = make_term(a->coeff, a->exp);
			new = new->next;
			a = a->next;
			printf("hello\n");
		}

		else if(b)
		{
			new->next = make_term(b->coeff, b->exp);
			new = new->next;
			printf("b\n");
			b = b->next;
		}
	}

	return head;
}


polynomial *sub_poly(polynomial *a, polynomial *b)
{
	struct term *new = make_term(0, 0);
	struct term *head = new;

	/*
	while(b)
	{
		b->coeff *= -1;
		b = b->next;
	}
	*/


	while(a || b) 
	{
		if (a && b)
		{
			if (a->exp > b->exp)
			{
				new->coeff = a->coeff;
				new->exp = a->exp;
				new->next = make_term(0,0);
				new = new->next;
				a = a->next;
			}
			else if(a->exp < b->exp)
			{

				new->coeff = b->coeff;
				new->exp = b->exp;
				new->next = make_term(0,0);
				new = new->next;
				b = b->next;
			}
			else if(a->exp == b->exp)
			{
				new->coeff = a->coeff - b->coeff;
				new->exp = b->exp;
				new->next = make_term(0,0);
				new = new->next;
				a = a->next;
				b = b->next;
			}
		}
		else if(a)
		{
			new->next = make_term(a->coeff, a->exp);
			new = new->next;
			a = a->next;
		}
		else if(b)
		{
			new->next = make_term(b->coeff, b->exp);
			new = new->next;
			b = b->next;
		}

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
