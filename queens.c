#include <stdio.h>
#include "board.h"
#include "trie.h"

#define LEN 5

/*
 * _queens: Recursively look for solutions to the queens problem.
 */
int _queens(Board *qb, Trie **trie, int *len, int *num)
{
	int i, j;

	if (*len == LEN) {
		(*num)++;
		tTrie_add_n_char(trie, LEN*LEN, qb->board);
	} else {
		for (j = 0; j < LEN; j++) {
			for (i = 0; i < LEN; i++)
			{
				if (qB_validate(qb, i, j))
					continue;
				// choose
				qB_place_queen(qb, i, j, 0);
				// explore
				(*len)++;
				_queens(qb, trie, len, num);
				// un choose
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
	int num, len, length;
	num = len = 0;
	length = LEN;
	qb = qB_new(qb, length);
	_queens(qb, trie, &len, &num);

	tTrie_output(trie, qB_print_board, (void*)&length);

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
