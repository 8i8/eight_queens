#ifndef board_h
#define board_h
typedef struct Board {
	char *board;
	int total_len;
	int len;
} Board;
#endif

/* qB_new: Initialise a new board */
Board *qB_new(Board *qb, int len);

/* qB_validate: Is the square available? */
int qB_validate(Board *qb, int x, int y);

/* qB_place_queen: Add a new queen to the board after a validation of the
 * square, the validation can be overidden for the case in which a verification
 * has already been made. */
int qB_place_queen(Board *qb, int x, int y, int validate);

/* qB_remove_queen: Remove queen after solution attempt. */
int qB_remove_queen(Board *qb, int x, int y, int validate);

/* qB_print: Print out the board with the queens positions. */
void qB_print(Board *qb, int num);

/* qB_print_board: Print in board format from a Board internal string, used by
 * trie.c for output; Takes a string and the length of one side of the square
 * board. */
void qB_print_board(void *b, void* l, int index);

/* qB_print_board_with_info: Print in board format from a Board internal
 * string, the availability of squares, this is the underlying matrix for the
 * queens sight; For fast access by checking check a 3rd dimension used to
 * increment a numerical value in any squares that are covered by a queens
 * sight. */
void qB_print_board_with_info(Board *qb);

/* qB_free(Board *qb) */
void qB_free(Board *qb);
