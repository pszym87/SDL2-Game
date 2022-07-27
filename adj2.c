#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define H_SIZE 3
#define W_SIZE 4
#define V H_SIZE*W_SIZE
void generateAdjMatrix();
void printMatrix(int adj[H_SIZE*W_SIZE][H_SIZE*W_SIZE], int size);

void printSolution(int dist[]);
int minDistance(int dist[], bool sptSet[]);

void dijkstra(int graph[V][V], int src);
int b[H_SIZE][W_SIZE] = {
		  {1, -1, -1,-1},
		  {-1,-1, 1, 1},
		  {1,-1,-1, 1}};

/*
int b[H_SIZE][W_SIZE] = {
{ -1,  1, 10,  1,  1, -1, -1,  1, -1,  1, -1, -1,  1,  1, -1,  1,  1, -1},
{ -1,  1, -1,  1,  1, -1,  1,  1,  1,  1, -1, -1,  1,  1, -1,  1,  1, -1},
{ -1 , 1, -1,  1,  1, -1,  1,  1,  1,  1, -1, -1,  1,  1, -1,  -1,  1, -1},
{  1,  1,  1,  1,  1, -1,  1,  1,  1,  1, -1, -1,  1,  1, -1,  1,  1, -1},
{ -1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
{401,  1 , 1 ,  1 , 1 ,  -1, -1 , -1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1},
{  1 , -1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, -1, -1, -1, 1, 1, -1, 1, 1, 1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1, -1, -1, 1, -1, -1, -1, 1, 1, -1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, 1, 1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, -1, -1, -1, 1, 1,  1, -1, -1, 1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1,  1, 1,  -1, -1},
{ -1 ,  1 ,  1 ,  1 , 1 ,   1,  1 ,1, 400, 1, -1, -1, 1, 1, -1, 1, -1, -1},
{ -1 ,  1 , -1 ,  1 , -1 ,  -1, -1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1, -1 ,1, 1, 1,  1, -1, 1, 1, -1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , -1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, -1, -1, -1, 1, 1, -1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1, -1, -1 , -1, 1, -1, -1, 1, 1, -1, 4, 1, -1},
{ -1 ,  1 , -1 ,  -1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1,  1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1,  1, 1, 1, -1},
{  1 ,  1 ,  1 ,  1 , 1, -1,  1 ,1, 1, 1, -1, -1, 1, 402, -1, 1, 1, 1},
{ -1 , -1 , -1 ,  1 , 1 ,  -1,  1 , -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1},
{  1 ,  1 , -1 ,  1 , 1 ,  -1, -1 ,-1, 1, -1, -1, -1, 1,  1, -1, 1, 1,  1},
{ -1 , -1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, 1, 1, 1, -1},
{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, 1, 1, 1, -1},
{ -1 ,  1 , -1 , -1 , -1 ,  -1,  1 ,1, -1, 1, -1, -1, 1, 1, -1, 1, 1, -1}
};
*/
int main(){
	
	int adj[H_SIZE*W_SIZE][H_SIZE*W_SIZE];
	
	generateAdjMatrix(adj);
	dijkstra(adj, 0);	

	return 0;
}

/** \brief Funkcja tworzy z tablicy dwuwymiarowej (mapy gry) macierz sąsiedztwa
 *
 *	w ktorej koszt krawedzi jest identyczny i rowna sie 0
**/

void generateAdjMatrix(int adj[H_SIZE*W_SIZE][H_SIZE*W_SIZE]){
	int n = H_SIZE;
	int m = W_SIZE;
//	int b[][] = board;
	//int adj[n*m][n*m];
	
	//memset
	memset(adj, 0, sizeof(int)*n*m*n*m);

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			
			if(b[i][j] >-1){
				// sprawdz sasiadow
				int x = (i-1 < 0) ? n-1 : i-1;
				int y = (i+1 > n-1) ? 0 : i+1;
				int z = (j-1 < 0) ? m-1 : j-1;
				int w = (j+1 > m-1) ? 0 : j+1;
				
				if(b[x][j] > 0) adj[i*m+j][x*m+j] = 1;  
				if(b[y][j] > 0) adj[i*m+j][y*m+j] = 1;
				if(b[i][z] > 0) adj[i*m+j][i*m+z] = 1;
				if(b[i][w] > 0) adj[i*m+j][i*m+w] = 1;

		}}

	}
	
	printMatrix(adj, H_SIZE*W_SIZE);

}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}
  
// A utility function to print the constructed distance array
void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
  
// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i
    int prev[V]; //indeksy to wierzcholek, wartosc to kto jest poprzednikiem

	memset(prev, -1, sizeof(int)*V); 
 
    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
  
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
  
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
  
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);
  
        // Mark the picked vertex as processed
        sptSet[u] = true;
  
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
  
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v], prev[v]=u;
    }
  
    // print the constructed distance array
    printSolution(dist);
    
	for(int i=0; i<V; i++){
		printf("prev[%d] = %d\n", i, prev[i]);
	}
}	

void printMatrix(int adj[H_SIZE*W_SIZE][H_SIZE*W_SIZE], int size){
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			printf("%d\t", adj[i][j]);	
		}
	printf("\n");
	}
}
