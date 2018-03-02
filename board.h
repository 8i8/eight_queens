
typedef struct Board {
	char *board;
	int total_len;
	int len;
} Board;

Board *qB_new(Board *qb, int len);
int qB_place_queen(Board *qb, int x, int y, int validate);
void qB_print(Board *qb);
void qB_print_disponibility(Board *qb);
void qB_free(Board *qb);
