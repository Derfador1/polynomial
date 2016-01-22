#include "polynomial.h"

#include <stdio.h>
#include <stdlib.h>

void transform(struct term *stuff)
{
	printf("%d", stuff->coeff);	
}

int main(void)
{

	struct term *new = make_term(-5, 8);
	struct term *new1 = make_term(4, 2);
	struct term *new2 = make_term(1, 2);
	//struct term *new3 = make_term(5, 0);

	polynomial *sum = add_poly(new, new1);

	polynomial *sub = sub_poly(sum, new2);


	printf("fshd\n");
	poly_to_string(new);

	printf("sum\n");
	poly_print(sum);

	printf("\n");

	printf("sub\n");
	poly_print(sub);

	char *buffer = poly_to_string(sub);

	printf("\nFinal: %s\n", buffer);

	if(is_equal(new, sub))
		printf("they match\n");
	else
		printf("they do not match\n");


	printf("\n");

	free(buffer);
	poly_free(new);
	poly_free(new1);
	poly_free(new2);
	poly_free(sum);
	poly_free(sub);
}
