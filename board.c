#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _clear_board(Board *qb)
{
	int i, j, k, len = qb->len;
	char *board;
	board = qb->board;

	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			for(k = 0; k < 2; k++)
				*(board+i+(j*len)+(k*len*len)) = '+';
}

Board *qB_new(Board *qb, int len)
{
	qb = malloc(sizeof(Board));
	qb->len = len;
	qb->total_len = len * len * 2;
	qb->board = malloc(2 * len * len);

	_clear_board(qb);

	return qb;
}

void _set_queen(Board *qb, int x, int y)
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
}

int qB_validate(Board *qb, int x, int y)
{
	int len = qb->len;
	char *board;
	board = qb->board;

	if (*(board+x+(y * len)+(len * len)) == '-')
		return -1;
	return 0;
}

int qB_place_queen(Board *qb, int x, int y)
{
	if (qB_validate(qb, x, y))
		return -1;

	_set_queen(qb, x, y);

	return 0;
}

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
