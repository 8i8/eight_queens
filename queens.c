#include <stdio.h>
#include "board.h"

#define LEN 8

int _queens(Board *qb, int len, int *num)
{
	int i, j;

	qB_print_with_info(qb, *num);

	if (len == 0) {
		//qB_print(qb, *num);
		//qB_print_with_info(qb, *num);
		(*num)++;
		return 0;
	} else {
		for (i = 0; i < LEN; i++) {
			for (j = 0; j < LEN; j++) {

				if (qB_validate(qb, i, j))
					continue;
				// choose
				qB_place_queen(qb, i, j, 0);
				if (len == 0)
					return 0;
				// explore
				if (_queens(qb, --len, num))
					return 0;
				// un-chose
				qB_remove_queen(qb, i, j, 1);
			}
		}
	}

	return 0;
}

int queens(int len)
{
	int num = 0;
	Board *qb = NULL;
	qb = qB_new(qb, len);
	_queens(qb, len, &num);

	//qB_place_queen(qb, 3, 3, 0);
	//qB_print(qb);
	//qB_print_disponibility(qb);

	qB_free(qb);
	return 0;
}

int main(void)
{
	if (queens(LEN))
		return -1;

	return 0;
}
