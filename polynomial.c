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

	//tmp_head->next->coeff = 1;
	//tmp_head->next->exp = 2;

	while(tmp_head) {
		storage = realloc(storage, 50);
		coeff = tmp_head->coeff;
		exp = tmp_head->exp;

		snprintf(storage, 50, "+%dx^%d", coeff, exp);
		strcat(str, storage);
		printf("here : %s\n", storage);
		printf("here : %s\n", str);

		tmp_head = tmp_head->next;
	}
	return str;
}

polynomial *add_poly(polynomial *a, polynomial *b)
{
	//needs to be a while loop to check for number of terms to make a tmp for
	struct term *new = make_term(0, 0);
	struct term *head = node;
	//the head of the list is the tmp i am returning

	while(tmp_a) {
		while(tmp_b) {
			printf("%dx^%d\n", tmp_a->coeff, tmp_a->exp);
			printf("%dx^%d\n", tmp_b->coeff, tmp_b->exp);

			if (tmp_a->exp > tmp_b->exp)
			{
				tmp_a->next = tmp_b;
				poly_print(tmp_a);
			}
			else if(tmp_a->exp < tmp_b->exp)
			{
				tmp_b->next = tmp_b;
				printf("%dx^%d\n", tmp_a->next->coeff, tmp_a->next->exp);
			}
			else
			{
				tmp_a->coeff = tmp_a->coeff + tmp_b->coeff;
				printf("%dx^%d\n", tmp_a->coeff, tmp_a->exp);
			}

			tmp_b = tmp_b->next;
		}
		tmp_a = tmp_a->next;
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
