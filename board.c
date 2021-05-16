#include "board.h"
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * clear_board: set all squares to the came value.
 */
int clear_board(Board *qb)
{
	if (qb == NULL)
		return -1;

	int i, j, k, len = qb->len;
	char *board;
	board = qb->board;

	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			for(k = 0; k < 2; k++)
				if (k == 0)
					*(board+i+(j*len)+(k*len*len)) = '.';
				else if (k == 1)
					*(board+i+(j*len)+(k*len*len)) = '0';
	*(board+qb->total_len) = '\0';

	return 0;
}

/*
 * qB_new: Initialise a new board.
 */
Board *qB_new(Board *qb, int len)
{
	qb = malloc(sizeof(Board));

	if (qb == NULL)
		return NULL;

	qb->len = len;
	qb->total_len = len * len * 2;
	qb->board = malloc(qb->total_len+1);

	clear_board(qb);

	return qb;
}

/*
 * set_queen: Add a queen to the primary board and mark all squares that are
 * covered by the queens sight on the 3rd dimension of the same.
 */
int set_queen(Board *qb, int x, int y, int quant)
{
	int i, sqr, len = qb->len;
	char *board;
	board = qb->board;
	sqr = len * len;

	/* Either place or remove a queen, depending on the value of quant. */
	if (quant == 1)
		*(board+x+(y*len)) = 'Q';
	else
		*(board+x+(y*len)) = '.';

	/* 3rd dimention for the queens 'regard' */
	for (i = 0; i < len; i++) {

		/* Rows and columns, */
		*(board+i+(y*len)+sqr) += quant;
		*(board+x+(i*len)+sqr) += quant;

		/* Diagonals */
		if (i <= x && i <= y)
			*(board + (x - i) + ((y - i) * len) + sqr) += quant;
		if (i < (len - x) && i <= y && i > 0)
			*(board + (x + i) + ((y - i) * len) + sqr) += quant;
		if (i <= x && i < (len - y) && i > 0)
			*(board + (x - i) + ((y + i) * len) + sqr) += quant;
		if (i < (len - x) && i < (len - y) && i > 0)
			*(board + (x + i) + ((y + i) * len) + sqr) += quant;
	}
	*(board+x+(y*len)+sqr) -= 2 * quant;

	return 0;
}

/*
 * qB_validate: Is the square available?
 */
int qB_validate(Board *qb, int x, int y)
{
	int len = qb->len;

	if (*(qb->board+x+(y * len)+(len * len)) > '0')
		return -1;

	return 0;
}

/*
 * qB_place_queen: Add a new queen to the board after a validation of the
 * square, the validation can be overridden for the case in which a verification
 * has already been made.
 */
int qB_place_queen(Board *qb, int x, int y, int validate)
{
	if (validate && qB_validate(qb, x, y))
		return -1;

	if (set_queen(qb, x, y, 1))
		return -1;

	return 0;
}

/*
 * qB_remove_queen: Remove queen after solution attempt.
 */
int qB_remove_queen(Board *qb, int x, int y, int validate)
{
	if (validate && *(qb->board+x+(y * qb->len)) != 'Q')
		return -1;

	if (set_queen(qb, x, y, -1))
		return -1;
	return 0;
}

/*
 * qB_print: Print out the board with the queens positions.
 */
void qB_print(Board *qb, int num)
{
	int i, sqr, len = qb->len;
	char *b_pt, buffer[len * len * 2 + len + 1];
	char *board;
	board = qb->board;
	b_pt = buffer;
	sqr = len * len;

	printf("%d\n", num);

	for (i = 0; i < sqr; i++) {
		snprintf(b_pt, 3, "%c ", *(board+i));
		b_pt += 2;
		if (!((i+1)%len))
			*b_pt++ = '\n';
	}
	*b_pt++ = '\0';
	printf("%s\n", buffer);
}

/*
 * qB_print_board: Print in board format from a Board internal string, used by
 * trie.c for output; Takes a string and the length of one side of the square
 * board.
 */
void qB_print_board(void *b, void* l, int index)
{
	char *board;
	int *l_pt;
	board = (char*)b;
	l_pt = (int*)l;
	int i, j, len = *l_pt;
	char *b_pt, buffer[(len * len * 2 + len) + 1];
	b_pt = buffer;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			snprintf(b_pt, 3, "%c ", *(board+i*len+j));
			b_pt += 2;
		}
		*(b_pt-1) = '\n';
	}
	*b_pt++ = '\0';
	printf("%d\n%s\n", index, buffer);
}

/*
 * qB_print_board_with_info: Print in board format from a Board internal
 * string, used by trie.c for output; Takes a string and the length of one side
 * of the square board.
 */
void qB_print_board_with_info(Board *qb)
{
	int i, j, sqr, len = qb->len;
	char *b_pt, buffer[(len * len * 2 + len) * 2 + 1];
	b_pt = buffer;
	sqr = len * len;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			snprintf(b_pt, 3, "%c ", *(qb->board+i*len+j));
			b_pt += 2;
		}
		*b_pt++ = ' ';
		for (j = 0; j < len; j++) {
			snprintf(b_pt, 3, "%c ", *(qb->board+i*len+sqr+j));
			b_pt += 2;
		}
		*(b_pt-1) = '\n';
	}
	*b_pt++ = '\0';
	printf("%s\n", buffer);
}

/*
 * qB_free(Board *qb)
 */
void qB_free(Board *qb)
{
	free(qb->board);
	free(qb);
}
