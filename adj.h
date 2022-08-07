#pragma once
#include "logic.h"

#define QUEUE_HEAD -1

/**
 * \typedef queue_t
 * Typedef for integer queue item 
 */

typedef struct queue_s queue_t;

struct queue_s{
	queue_t *next;
	int value;
};

queue_t* create_queue();	
void push_q(queue_t *queue_front, int value);
int pop_q(queue_t **queue_front);
void print_queue(queue_t *queue_front);
bool is_empty(queue_t *queue);
void generateAdjMatrix(int b[BSIZE_HEIGHT][BSIZE_WIDTH], int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH]);
void printMatrix(int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH], int size);
void printSolution(int dist[]);
int minDistance(int dist[], bool sptSet[]);
void dijkstra(int graph[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH], int src, int prev[]);
index_t getBoardIndex(int vertex);
int getVertex(int i, int j);
int get_queue_item(queue_t *queue, int searched_indx);


