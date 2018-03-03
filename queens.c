#include <stdio.h>
#include "board.h"
#include "trie.h"

#define LEN 8

/*
 * _queens: Recursivly look for solutions to the queens problem.
 *  TODO this function currently stops at the first solution, find a way to
 *  calulate and count all solutions, a trie is likely required to make the
 *  timing sensible.
 */
int _queens(Board *qb, Trie **trie, int *len, int *num)
{
	int i, j;

	if (*len == LEN) {
		(*num)++;
		qB_print_with_info(qb, *num, *len);
		//qB_print(qb, *num);
		//qB_store(qb, trie);
		printf("%s", qb->board);
		return 1;
	} else {
		for (i = 0; i < LEN; i++) {
			for (j = 0; j < LEN; j++) {

				if (qB_validate(qb, i, j))
					continue;
				// choose
				qB_place_queen(qb, i, j, 0);

				// explore
				(*len)++;
				if (_queens(qb, trie, len, num))
					return 1;

				// un-chose
				qB_remove_queen(qb, i, j, 1);
				(*len)--;
			}
		}
	}
	return 0;
}

int queens(void)
{
	Board *qb = NULL;
	Trie **trie = NULL;
	trie = tTrie_init(trie);
	int num, len;
	num = len = 0;
	qb = qB_new(qb, LEN);
	_queens(qb, trie, &len, &num);

	//tTrie_print(trie);

	//qB_place_queen(qb, 3, 3, 0);
	//qB_print_with_info(qb, num);

	qB_free(qb);
	tTrie_free(trie);

	return 0;
}

int main(void)
{
	if (queens())
		return -1;

	return 0;
}
