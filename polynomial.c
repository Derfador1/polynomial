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
	struct term *tmp_head = p;
	char *str = malloc(50);
	char *storage = malloc(50);
	int coeff = 0;
	int exp = 0;


	while(tmp_head->next) {
		storage = realloc(storage, 50);
		coeff = tmp_head->coeff;
		exp = tmp_head->exp;

		snprintf(storage, 50, "+%dx^%d", coeff, exp);
		strcat(str, storage);
		printf("\n");
		printf("Storage : %s\n", storage);
		printf("Str : %s\n", str);

		tmp_head = tmp_head->next;
	}
	return str;
}

polynomial *add_poly(polynomial *a, polynomial *b)
{
	struct term *new = make_term(0, 0);
	struct term *head = new;
	//the head of the list is the tmp i am returning

	while(a && b) 
	{
		if (a->exp > b->exp)
		{
			new->coeff = a->coeff;
			new->exp = a->exp;
			if(a->next == NULL)
			{
				new->next = b;
				break;
			}
			new->next = make_term(0,0);
			new = new->next;
			a = a->next;
		}
		else if(a->exp < b->exp)
		{
			new->coeff = b->coeff;
			new->exp = b->exp;
			if(b->next == NULL)
			{
				new->next = a;
				break;
			}
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

	return head;
}


polynomial *sub_poly(polynomial *a, polynomial *b)
{
	struct term *new = make_term(0, 0);
	struct term *head = new;
	//the head of the list is the tmp i am returning

	while(a && b) 
	{
		if (a->exp > b->exp)
		{
			new->coeff = a->coeff;
			new->exp = a->exp;
			if(a->next == NULL)
			{
				new->next = b;
				break;
			}
			new->next = make_term(0,0);
			new = new->next;
			a = a->next;
		}
		else if(a->exp < b->exp)
		{
			new->coeff = b->coeff;
			new->exp = b->exp;
			if(b->next == NULL)
			{
				new->next = a;
				break;
			}
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

	return head;
}


bool is_equal(polynomial *a, polynomial *b)
{
	//struct term *tmp_a = a;
	//struct term *tmp_b = b;
	while(a && b) {
		if(a->coeff == b->coeff && a->exp == b->exp)
		{
			a = a->next;
			b = b->next;
		}
		else
		{
			return false;
		}
	}

	return true;

}
