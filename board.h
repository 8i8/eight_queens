
typedef struct Board {
	char *board;
	int total_len;
	int len;
} Board;

Board *qB_new(Board *qb, int len);
int qB_place_queen(Board *qb, int x, int y, int validate);
int qB_remove_queen(Board *qb, int x, int y, int validate);
int qB_validate(Board *qb, int x, int y);
void qB_print(Board *qb, int num);
void qB_print_with_info(Board *qb, int num, int queens);
void qB_free(Board *qb);
