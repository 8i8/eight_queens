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
				if (k == 0)
					*(board+i+(j*len)+(k*len*len)) = '.';
				else if (k == 1)
					*(board+i+(j*len)+(k*len*len)) = '0';
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
int _set_queen(Board *qb, int x, int y, int quant)
{
	int i, j, len = qb->len;
	char *board;
	board = qb->board;

	if (quant == 1)
		*(board+x+(y*len)) = 'Q';
	else
		*(board+x+(y*len)) = '.';

	for (i = 0; i < len; i++) {

		/* Rows and columns */
		if (i == y)
			for (j = 0; j < len; j++)
				if (j != i)
					*(board+j+(i*len)+(len * len)) += quant;
		if (i == x)
			for (j = 0; j < len; j++)
				if (j != i)
					*(board+i+(j*len)+(len * len)) += quant;

		/* Diagonals */
		if (i <= x && i <= y)
			*(board + (x - i) + ((y - i) * len) + (len * len)) += quant;
		if (i <= (len - x) && i <= y && i > 0)
			*(board + (x + i) + ((y - i) * len) + (len * len)) += quant;
		if (i <= x && i <= (len - y) && i > 0)
			*(board + (x - i) + ((y + i) * len) + (len * len)) += quant;
		if (i <= (len - x) && i <= (len - y) && i > 0)
			*(board + (x + i) + ((y + i) * len) + (len * len)) += quant;
	}

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
 * square, the validation can be overidden for the case in which a verification
 * has already been made.
 */
int qB_place_queen(Board *qb, int x, int y, int validate)
{
	if (validate && qB_validate(qb, x, y))
		return -1;

	if (_set_queen(qb, x, y, 1))
		return -1;

	return 0;
}

int qB_remove_queen(Board *qb, int x, int y, int validate)
{
	if (validate && *(qb->board+x+(y * qb->len)) != 'Q')
		return -1;

	if (_set_queen(qb, x, y, -1))
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
 * qB_print_with_info: Print out the state of the board, the avaliablilty
 * of squares, this is the underlying matrig of the queens sight; For fast
 * avalibilty check a 3rd dimention has been used to store '-' in squares that
 * are covered by a queens sight.
 */
void qB_print_with_info(Board *qb, int num)
{
	int i, j, sqr, len = qb->len;
	char *b_pt, buffer[(len * len * 2 + len) * 2 + 1];
	char *board;
	board = qb->board;
	b_pt = buffer;
	sqr = len * len;

	printf("%d\n", num);

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			snprintf(b_pt, 3, "%c ", *(board+i*len+j));
			b_pt += 2;
		}
		*b_pt++ = ' ';
		for (j = 0; j < len; j++) {
			snprintf(b_pt, 3, "%c ", *(board+i*len+sqr+j));
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
