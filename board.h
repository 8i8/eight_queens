typedef struct Board {
	char *board;
	int total_len;
	int len;
} Board;

#ifndef _trie_h
#define _trie_h
typedef struct Trie {
	int c;
	struct Trie **next;
	int word_end;
} Trie;
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

/* qB_print_with_info: Print out the state of the board, the avaliablilty
 * of squares, this is the underlying matrix for the queens sight; For fast
 * avalibilty check a 3rd dimention has been used to store '-' in squares that
 * are covered by a queens sight. */
void qB_print_with_info(Board *qb, int num, int queens);

/* qB_store: Write board into trie data structure. */
int qB_store(Board *qb, Trie **trie);

/* qB_free(Board *qb) */
void qB_free(Board *qb);
