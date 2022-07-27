#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "adj.h"

#pragma once

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

	printMatrix(adj, n*m);
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
  
    // print the constructed distance array
    printSolution(dist);
    
	for(int i=0; i<BSIZE_HEIGHT*BSIZE_WIDTH; i++){
		printf("prev[%d] = %d\n", i, prev[i]);
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
