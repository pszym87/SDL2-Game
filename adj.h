#include "logic.h"

void generateAdjMatrix(int b[BSIZE_HEIGHT][BSIZE_WIDTH], int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH]);
void printMatrix(int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH], int size);
void printSolution(int dist[]);
int minDistance(int dist[], bool sptSet[]);
void dijkstra(int graph[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH], int src, int prev[]);
index_t getBoardIndex(int vertex);
int getVertex(int i, int j);
