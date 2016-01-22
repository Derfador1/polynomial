#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct term {
	int coeff;
	int exp;
	struct term *next;
};

typedef struct term polynomial;

struct term *make_term(int coeff, int exp);
void poly_free(polynomial *eqn);
void poly_print(polynomial *eqn);
char *poly_to_string(polynomial *p);
polynomial *add_poly(polynomial *a, polynomial *b);
polynomial *sub_poly(polynomial *a, polynomial *b);
