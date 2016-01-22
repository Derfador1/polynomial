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

	int coeff = 0;
	int exp = 0;


	while(p->next) {
		storage = realloc(storage, sizeof(storage)+25);
		coeff = p->coeff;
		exp = p->exp;

		snprintf(storage, sizeof(storage)+25, "+%dx^%d", coeff, exp);
		strncat(str, storage, 50);

		p = p->next;

	}

	free(storage);
	return str;
}

polynomial *add_poly(polynomial *a, polynomial *b)
{
	struct term *new = make_term(0, 0);
	struct term *head = new;

	while(a && b) 
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
			new->coeff = b->coeff + a->coeff;
			new->exp = b->exp;
			new->next = make_term(0,0);
			new = new->next;
			a = a->next;
			b = b->next;
		}
	}

	if(a)
	{
		new->next = make_term(a->coeff, a->exp);
		a = a->next;
	}
	else if(b)
	{
		new->next = make_term(b->coeff, b->exp);
		b = b->next;
	}

	return head;
}


polynomial *sub_poly(polynomial *a, polynomial *b)
{
	struct term *new = make_term(0, 0);
	struct term *head = new;

	while(a && b) 
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

	if(a)
	{
		new->next = make_term(a->coeff, a->exp);
		a = a->next;
	}
	else if(b)
	{
		new->next = make_term(b->coeff, b->exp);
		b = b->next;
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
