#include "polynomial.h"

#include <stdio.h>
#include <stdlib.h>

void transform(struct term *stuff)
{
	printf("%d", stuff->coeff);	
}

int main(void)
{

	struct term *new = make_term(5, 8);
	struct term *new1 = make_term(2, 2);
	struct term *new2 = make_term(-4, 3);
	struct term *new3 = make_term(1, 2);

	poly_print(new);
	poly_print(new1);
	polynomial *sum = add_poly(new, new1);
	printf("\n");
	poly_print(sum);
	printf("\n");
	polynomial *sum1 = add_poly(sum, new3);
	poly_print(sum1);
	printf("\n");
	char *buffer = poly_to_string(sum1);
	printf("Final: %s\n", buffer);
	printf("\n");

	/*
	if(is_equal(new, sum))
		printf("they match\n");
	else
		printf("they do not match\n");
	*/


	printf("\n");

	//free(buffer1);
	poly_free(new);
	poly_free(new1);
	poly_free(new2);
	//poly_free(sum);
	//poly_free(sub);
}
