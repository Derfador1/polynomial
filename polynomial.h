#include <stdio.h>
#include <stdlib.h>

struct term {
	int coeff;
	int exp;
	struct term *next;
};

typedef struct term polynomial;

struct term *make_term(int coeff, int exp);
void poly_free(polynomial *eqn);
void poly_print(polynomial *eqn);
