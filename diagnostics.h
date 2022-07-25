#include "logic.h"

void twoPlayersPlay(index_t *marioIndex, index_t *ghostIndex, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);
void onePlayerPlay(index_t *marioIndex, index_t *ghostIndex, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);
void printTheBoard(int board[BSIZE_HEIGHT][BSIZE_WIDTH]);
void printIndexPosition(index_t position);
