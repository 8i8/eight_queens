#include <stdio.h>
#include "board.h"

#define LEN 8

int main(void)
{
	Board *qb = NULL;
	qb = qB_new(qb, LEN);

	//if (qB_place_queen(qb, 0, 0))
	//	printf("failed to place queen\n");
	if (qB_place_queen(qb, 2, 4))
		printf("failed to place queen\n");

	qB_print(qb);
	putchar('\n');
	qB_print_disponibility(qb);

	return 0;
}
