#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * _clear_board: set all squares to the came value.
 */
int _clear_board(Board *qb)
{
	if (qb == NULL)
		return -1;

	int i, j, k, len = qb->len;
	char *board;
	board = qb->board;

	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			for(k = 0; k < 2; k++)
				*(board+i+(j*len)+(k*len*len)) = '+';
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
	qb->board = malloc(2 * len * len);

	_clear_board(qb);

	return qb;
}

/*
 * _set_queen: Add a queen to the primary board and mark all squares that are
 * coverd by the queens sight on the 3rd dimention of the same.
 */
int _set_queen(Board *qb, int x, int y)
{
	int i, j, len = qb->len;
	char *board;
	board = qb->board;

	*(board+x+(y*len)) = 'Q';

	for (i = 0; i < len; i++) {

		/* Rows and columns */
		if (i == y)
			for (j = 0; j < len; j++)
				*(board+j+(i*len)+(len * len)) = '-';
		if (i == x)
			for (j = 0; j < len; j++)
				*(board+i+(j*len)+(len * len)) = '-';

		/* Diagonals */
		if (i <= x && i <= y)
			*(board + (x - i) + ((y - i) * len) + (len * len)) = '-';
		if (i <= (len - x) && i <= y)
			*(board + (x + i) + ((y - i) * len) + (len * len)) = '-';
		if (i < x && i < (len - y))
			*(board + (x - i) + ((y + i) * len) + (len * len)) = '-';
		if (i < (len - x) && i < (len - y))
			*(board + (x + i) + ((y + i) * len) + (len * len)) = '-';
	}

	return 0;
}

/*
 * qB_validate: Is the square available?
 */
int qB_validate(Board *qb, int x, int y)
{
	int len = qb->len;

	if (*(qb->board+x+(y * len)+(len * len)) == '-')
		return -1;

	return 0;
}

/*
 * qB_place_queen: Add a new queen to the board after a validation of the
 * square, the validation can be overidden for the case in which a verification
 * has already been made.
 */
int qB_place_queen(Board *qb, int x, int y, int validate)
{
	if (validate && qB_validate(qb, x, y))
		return -1;

	if (_set_queen(qb, x, y))
		return -1;

	return 0;
}

/*
 * qB_print: Print out the board with the queens positions.
 */
void qB_print(Board *qb)
{
	int i, len = qb->len;
	char *b_pt, buffer[len * len + len + 1];
	char *board;
	board = qb->board;
	b_pt = buffer;

	for (i = 0; i < len; i++) {
		memcpy(b_pt, board+(i*len), len);
		b_pt += len;
		*b_pt++ = '\n';
		*b_pt = '\0';
	}
	*b_pt++ = '\0';
	printf("%s", buffer);
}

/*
 * qB_print_disponibility: Print out the state of the board, the avaliablilty
 * of squares, this is the underlying matrig of the queens sight; For fast
 * avalibilty check a 3rd dimention has been used to store '-' in squares that
 * are covered by a queens sight.
 */
void qB_print_disponibility(Board *qb)
{
	int i, len = qb->len;
	char *b_pt, buffer[len * len + len + 1];
	char *board;
	board = qb->board;
	b_pt = buffer;

	for (i = 0; i < len; i++) {
		memcpy(b_pt, board+(i*len)+(len*len), len);
		b_pt += len;
		*b_pt++ = '\n';
		*b_pt = '\0';
	}
	*b_pt++ = '\0';
	printf("%s", buffer);
}

/*
 * qB_free(Board *qb)
 */
void qB_free(Board *qb)
{
	free(qb->board);
	free(qb);
}
