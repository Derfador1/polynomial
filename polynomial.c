#include "polynomial.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char *str = malloc(50);
	int i = 0;

	while(p->coeff) {
		if(p->exp > 1) {
			//str[i] = ((char)p->coeff);
			//printf("%d\n", str[i]);
			printf("%c%d", p->coeff > 0 ? '+' : '\0', p->coeff);
			printf("x^%d", p->exp);	
			break;
		}
		else if(p->exp == 1) {
		}
	}
}

polynomial *add_poly(polynomial *a, polynomial *b)
{
	struct term *tmp = malloc(sizeof(*tmp));

	while(a && b != NULL) {
		if (a->exp == b->exp) {
			tmp->coeff = a->coeff + b->coeff;
			printf("%dx^%d\n", tmp->coeff, a->exp);
		}
		a = a->next;
		b = b->next;
	}
}

polynomial *sub_poly(polynomial *a, polynomial *b)
{
	struct term *tmp = malloc(sizeof(*tmp));

	while(a && b != NULL) {
		if (a->exp == b->exp) {
			tmp->coeff = a->coeff - b->coeff;
			printf("%dx^%d\n", tmp->coeff, a->exp);
		}
		a = a->next;
		b = b->next;
	}
}
