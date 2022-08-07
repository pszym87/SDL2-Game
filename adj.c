#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "adj.h"
#include <stdlib.h>

/** \brief Funkcja tworzy z tablicy dwuwymiarowej (mapy gry) macierz sąsiedztwa
 *
 *	\param board[][]  [IN] plansza gry
 *	\param adj[][]	  [OUT] macierz sasiedztwa dla planszy gry zaprezentowanej jako graf
**/

void generateAdjMatrix(int b[BSIZE_HEIGHT][BSIZE_WIDTH], int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH]){
	int n = BSIZE_HEIGHT; 
	int m = BSIZE_WIDTH;
	
	memset(adj, 0, sizeof(int)*n*m*n*m);

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			
			if(b[i][j] >-1){
				
				int x = (i-1 < 0) ? n-1 : i-1;
				int y = (i+1 > n-1) ? 0 : i+1;
				int z = (j-1 < 0) ? m-1 : j-1;
				int w = (j+1 > m-1) ? 0 : j+1;
				
				if(b[x][j] > 0) adj[i*m+j][x*m+j] = 1;  
				if(b[y][j] > 0) adj[i*m+j][y*m+j] = 1;
				if(b[i][z] > 0) adj[i*m+j][i*m+z] = 1;
				if(b[i][w] > 0) adj[i*m+j][i*m+w] = 1;
			}
		}

	}

}

index_t getBoardIndex(int vertex){
	index_t r;
	
	r.y = vertex / BSIZE_WIDTH;
	r.x = vertex % BSIZE_WIDTH;

	return r;
}

int getVertex(int i, int j){

	return i*BSIZE_WIDTH + j;
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < BSIZE_HEIGHT*BSIZE_WIDTH; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}
  
// A utility function to print the constructed distance array
void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < BSIZE_HEIGHT*BSIZE_WIDTH; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
  
// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH], int src, int prev[])
{
    int dist[BSIZE_HEIGHT*BSIZE_WIDTH]; // The output array.  dist[i] will hold the shortest
    // distance from src to i
    //int prev[V]; //indeksy to wierzcholek, wartosc to kto jest poprzednikiem

    memset(prev, -1, sizeof(int)*BSIZE_HEIGHT*BSIZE_WIDTH); 
 
    bool sptSet[BSIZE_HEIGHT*BSIZE_WIDTH]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
  
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < BSIZE_HEIGHT*BSIZE_WIDTH; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
  
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
  
    // Find shortest path for all vertices
    for (int count = 0; count < (BSIZE_HEIGHT*BSIZE_WIDTH)-1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);
  
        // Mark the picked vertex as processed
        sptSet[u] = true;
  
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < BSIZE_HEIGHT*BSIZE_WIDTH; v++)
  
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v], prev[v]=u;
    }
  
    
}	

void printMatrix(int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH], int size){
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			printf("%d\t", adj[i][j]);	
		}
	printf("\n");
	}
}


/**
 * \brief Create a queue and return its pointer to the head
 */

queue_t* create_queue(){	
	queue_t *queue_head = malloc(sizeof(queue_t)); 
	queue_head->value = QUEUE_HEAD;
	queue_head->next = NULL;
	
	return queue_head;
}

/**
 * \brief Push to the queue
 * Add new item to the end of the queue
 */
void push_q(queue_t *queue_front, int value){
	
	// create a new item
	queue_t *new_item = malloc(sizeof(queue_t));
	new_item->next = NULL;
	new_item->value = value;
		
	// find last item in the queue
	queue_t *curr_item = queue_front;
	while(curr_item->next != NULL) curr_item=curr_item->next;

	
	// append
	curr_item->next = new_item;
}

/** 
 * \brief Pop the queue
 * Access the front element of the queue. Read its value and set the next iteam as front.
 * 
 */
int pop_q(queue_t **queue_head){
	
	if((*queue_head)->next == NULL) return (*queue_head)->value;
	else{
		queue_t *queue_front = (*queue_head)->next;
		int ret = queue_front->value;
		
		queue_t* to_release = queue_front;
		(*queue_head)->next = queue_front->next;
		
		free(to_release);
		return ret;
	}
}

/**
 * \brief Check if the queue is empty. Empty queue contains only a head. 
 *
 */
bool is_empty(queue_t *queue){
	if(queue->value == QUEUE_HEAD && queue->next == NULL) return true;
	else return false;
}

/**
 * \brief Print contents of queue to stdout
 * 
 */
void print_queue(queue_t *queue_front){
	queue_t *curr_item = queue_front->next;

	while(curr_item != NULL){
		 printf("Item: %d\n", curr_item->value);
		 curr_item=curr_item->next;
	}
}


/** 
 * \brief Access a queue item by index position (equivalent to a[i] in arrays)
 * 
 * \return value stored in a queue at position queue[searched_indx]
 * \retval -1 queue is empty
 * \retval -2 searched_indx exceeds queue size
 */
int get_queue_item(queue_t *queue, int searched_indx){

	// if queue is empty 
	if(is_empty(queue)) return -1;
	else{
		// travese to the searched_indx
		int i=0;
		queue_t *curr_q_itm = queue;
		while(i<searched_indx && curr_q_itm != NULL){
			++i;
			curr_q_itm = curr_q_itm->next;
		}

		if(curr_q_itm != NULL) return curr_q_itm->value;
		else return -2;
	}
}
