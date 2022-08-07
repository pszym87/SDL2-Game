#include "logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "adj.h"

void moveGhosts(game_t *myGame){
	srand(time(0));
	index_t move3 = generateRandomPossibleMove(myGame->ghostIndex+1, myGame->board);
	index_t move4 = genRandFwd(*(myGame->ghostIndex+2), myGame->adj); 
	moveGhostDijkstra(myGame);

	moveRespectingRules(move3, myGame, 1);
	moveRespectingRules(move4, myGame, 2);
}


void gameInit(game_t *myGame, int num){
	/*int tmp[BSIZE_HEIGHT][BSIZE_WIDTH] = {
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
	};*/

	int tmp[BSIZE_HEIGHT][BSIZE_WIDTH] = {
	{ -1,  1, 10,  1,  1, -1, -1,  1, -1,  1, -1, -1,  1,  400, -1,  1,  1, -1},
	{ -1,  1, -1,  1,  1, -1,  1,  1,  1,  1, -1, -1,  1,  1, -1,  1,  1, -1},
	{ -1 , 1, -1,  1,  1, -1,  1,  1,  1,  1, -1, -1,  1,  1, -1,  -1,  1, -1},
	{  1,  1,  1,  1,  1, -1,  1,  1,  1,  1, -1, -1,  1,  1, -1,  1,  1, -1},
	{ -1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
	{  1,  1 , 1 ,  1 , 1 ,  -1, -1 , -1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1},
	{  1 , -1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, -1, -1, -1, 1, 1, -1, 1, 1, 1},
	{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1},
	{ -1 ,  1 , -1 ,  1 , 1 ,  -1, -1, -1, 1, -1, -1, -1, 1, 1, -1, 1, 1, -1},
	{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, 1, 1},
	{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, -1, -1, -1, 1, 1,  1, -1, -1, 1},
	{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 1, 1, -1, -1, 1, 1,  1, 1,  -1, -1},
	{ -1 ,  1 ,  1 ,  1 , 1 ,   1,  1 ,1, 1, 1, -1, -1, 1, 1, -1, 1, -1, -1},
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
	{ -1 ,  1 , -1 ,  1 , 1 ,  -1,  1 ,1, 401, 1, -1, -1, 1, 1, 1, 1, 1, -1},
	{ -1 ,  1 , -1 , -1 , -1 ,  -1,  1 ,1, -1, 1, -1, -1, 1, 1, -1, 1, 1, -1}
	};
	memcpy(myGame->board, tmp, sizeof (int) *BSIZE_HEIGHT * BSIZE_WIDTH);	

	myGame->marioIndex = getAnIndexPositionOf(10,myGame->board);
	myGame->ghostIndex = malloc(sizeof(index_t)*num);
	
	for(int i=0; i<num; i++)
		*(myGame->ghostIndex+i) = getAnIndexPositionOf(400+i,myGame->board);
	
	myGame->ghost_num = num;
	myGame->gameStatus = SINTRO;	
	memset(myGame->keyb, 0, KEYB_LEN);
	myGame->playerMove = (index_t){0,0};

	generateAdjMatrix(myGame->board,myGame->adj);
}
void moveGhostDijkstra(game_t *myGame){

	//int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH];
	int prev[BSIZE_HEIGHT*BSIZE_WIDTH];
	//generateAdjMatrix(myGame->board,adj);
	int root = getVertex(myGame->marioIndex.y, myGame->marioIndex.x); 	
	dijkstra(myGame->adj, root, prev); 
	int ghost = getVertex(myGame->ghostIndex->y, myGame->ghostIndex->x);
	int ghost_prev = prev[ghost];
	
	index_t coordinate = getBoardIndex(ghost_prev);
	
	if( marioGhostsCollision(coordinate,myGame) ){
			myGame->gameStatus = SSTOP;
	}
	else{	
	swap(&myGame->board[myGame->ghostIndex->y][myGame->ghostIndex->x],
			 &myGame->board[coordinate.y][coordinate.x]);
	*myGame->ghostIndex = coordinate;		
	};
		
		
}

void movePlayer(game_t *myGame){
	moveRespectingRules_new(myGame);			
	myGame->playerMove = (index_t) {0,0};
}
 
int swap(int *miejsce1, int *miejsce2){
	int temp = *miejsce1;
	*miejsce1 = *miejsce2;
	*miejsce2 = temp;
	return *miejsce1 + *miejsce2;
}

int consumeAndSwap(int *miejsce1, int *miejsce2){
	if(*miejsce1 > *miejsce2) {
		*miejsce2 += *miejsce1;
		*miejsce1 = 0;
	} else{
		*miejsce1 += *miejsce2; 
		*miejsce2 = 0; 
	}
	return *miejsce1 + *miejsce2;	
}


index_t getAnIndexPositionOf(int value, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	for(int i=0; i<BSIZE_HEIGHT; i++)
		for(int j=0; j<BSIZE_WIDTH; j++)
			if(value == board[i][j])
				return (index_t){i,j};  					
}

bool ghostsMarioCollision(index_t p, game_t *gm){
	
	for(int i=0; i<gm->ghost_num; i++)
		if(p.x == gm->ghostIndex[i].x && p.y == gm->ghostIndex[i].y) return true;
	return false;  
}

bool marioGhostsCollision(index_t p, game_t *gm){
	if(p.x == gm->marioIndex.x && p.y == gm->marioIndex.y) return true;
	return false;  
}

void moveRespectingRules_new(game_t *gm){

	if(!(gm->playerMove.x==0 && gm->playerMove.y==0)){
		// Zmienia tablice w poniekad liste cykliczna
		// Pozwala to na wykonanie skokow figury z ostatniego indeksu do pierwszego i na odwrot

		int newPositionX = (gm->marioIndex.x + gm->playerMove.x);
		int newPositionY = (gm->marioIndex.y + gm->playerMove.y);
		
		if(newPositionY < 0) newPositionY = BSIZE_HEIGHT-1;
		if(newPositionX < 0) newPositionX = BSIZE_WIDTH-1;
		  
		if(newPositionY > BSIZE_HEIGHT-1) newPositionY = 0;
		if(newPositionX > BSIZE_WIDTH-1) newPositionX = 0; 

		printf("\nRequest dla pozycji:y=%d x=%d", newPositionY, newPositionX);
		// sprawdza czy ruch jest mozliwy do wykonania na boardzie (czy nie ma sciany)
		if(gm->board[newPositionY][newPositionX]==-1){
			// do nothing
		}
		if(gm->board[newPositionY][newPositionX]>=0){
			
			if( ghostsMarioCollision((index_t){newPositionY, newPositionX},gm) ){
				gm->gameStatus = SSTOP;
			}	

			else{
				//zamien pozycjami pacmana z "nagroda"
				printf("** ruch mario o x=%d y=%d **", gm->playerMove.x, gm->playerMove.y);
				int prize = consumeAndSwap(&gm->board[gm->marioIndex.y][gm->marioIndex.x],
					       &gm->board[newPositionY][newPositionX]);
				//if(prize>400)
				//	printf("\nYOU KINDA LOOSE\n");
				//	gm->gameStatus = SSTOP;
					

			//zaktualizuj koordynaty figury 
			gm->marioIndex.x = newPositionX;
			gm->marioIndex.y = newPositionY;
			}
		}
	}

}

void moveRespectingRules(index_t positionChangeRequest, game_t *gm, int gh_num){

	// Zmienia tablice w poniekad liste cykliczna
        // Pozwala to na wykonanie skokow figury z ostatniego indeksu do pierwszego i na odwrot

        int newPositionX = (gm->ghostIndex[gh_num].x + positionChangeRequest.x);
	int newPositionY = (gm->ghostIndex[gh_num].y + positionChangeRequest.y);
	
	if(newPositionY < 0) newPositionY = BSIZE_HEIGHT-1;
	if(newPositionX < 0) newPositionX = BSIZE_WIDTH-1;
	  
	if(newPositionY > BSIZE_HEIGHT-1) newPositionY = 0;
	if(newPositionX > BSIZE_WIDTH-1) newPositionX = 0; 

	printf("\nRequest dla pozycji:y=%d x=%d", newPositionY, newPositionX);
	// sprawdza czy ruch jest mozliwy do wykonania na boardzie (czy nie ma sciany)
	if(gm->board[newPositionY][newPositionX]==-1){
        	// do nothing
	}else if(gm->board[newPositionY][newPositionX]>=0){				
				//printf("You LOOSE!\n");
		if( marioGhostsCollision((index_t){newPositionY, newPositionX},gm) ){
				gm->gameStatus = SSTOP;
		}else{
		printf("** ruch potworka o x=%d y=%d **", positionChangeRequest.x, positionChangeRequest.y);
		swap(&gm->board[gm->ghostIndex[gh_num].y][gm->ghostIndex[gh_num].x],&gm->board[newPositionY][newPositionX]);
		gm->ghostIndex[gh_num].x = newPositionX;
		gm->ghostIndex[gh_num].y = newPositionY;
		}	
	}
	
	//zaktualizuj koordynaty figury 
}

index_t generateRandomPossibleMove(index_t *currentPositionOfFigure,int board[BSIZE_HEIGHT][BSIZE_WIDTH]){

	// counter of permissible moves
	int count_perm = 0;

	index_t mv_arr[4] = {MV_UP, MV_DOWN, MV_LEFT, MV_RIGHT};
	
	// setting up lists
	// -- 'current_node' is used for traversing through the list	
	mv_list_t *head, *current_node;
	head = malloc(sizeof(mv_list_t));
	head->next = NULL;	
	current_node = head;

	// generate a list of all permissible moves for a given position
	for(int i=0; i<sizeof mv_arr/sizeof(index_t); i++){
		 
		if(czyMozliwy(mv_arr[i], currentPositionOfFigure, board)){
			
			++count_perm;
			
			// assign the move to the list 
			mv_list_t *new_node = malloc(sizeof(mv_list_t));
			new_node->position = mv_arr[i];
			new_node->next = NULL;
			current_node->next = new_node;

			// sets up a new node as a current node
			current_node = new_node;

		} 
	}	
	
	// draw a move from the list 
	int drawn_mv_indx = rand() % count_perm+1;
	// pick up the move from the list
	current_node = head;
	while(drawn_mv_indx>0){
		current_node = current_node->next;
		--drawn_mv_indx;
	}

	// returned value stored here
	index_t ret = current_node->position;

	// memory cleanup
	int i=0;	
	current_node = head;	
	while(current_node != NULL){
		mv_list_t *to_release = current_node;
		current_node = current_node->next;
		free(to_release);
		i++;
	}
	return ret;

}	


index_t genRandFwd(index_t curr_pos, int graph[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH]){
	
	static int rec_visited = -1;	
	int size = BSIZE_HEIGHT*BSIZE_WIDTH;
 
	// translate matrix position to graph node index
	int curr_vrtx = getVertex(curr_pos.y, curr_pos.x); 	

	queue_t *neighb_q = create_queue();	
	int q_size = 0;

	// add all adjacent vertexex to the queue
	for(int i=0; i<size; i++)
		if(graph[curr_vrtx][i] == 1 && i!=rec_visited){
			push_q(neighb_q, i);
			++q_size;
		}

	// allow backward move if other option aren't avaiable
	if(q_size==0) push_q(neighb_q, rec_visited), ++q_size;
		
	// draw a vertex from the queue
	int drawn_q_indx = rand()%q_size+1;
	
	// get a vertex
	int drawn_vrtx = get_queue_item(neighb_q, drawn_q_indx);
	
	int p_rec_visited = rec_visited; // temporary, for debugging
	rec_visited = curr_vrtx;
	
	// translate it to the relative coordinates
	index_t	ret = getBoardIndex(drawn_vrtx);
	ret.x = ret.x-curr_pos.x;
	ret.y = ret.y-curr_pos.y;

	return ret;
}

int czyMozliwy(index_t positionChangeRequest, index_t *currentPositionOfFigure, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	int newPositionX = (currentPositionOfFigure->x + positionChangeRequest.x);
	int newPositionY = (currentPositionOfFigure->y + positionChangeRequest.y);
	
	newPositionY += (newPositionY < 0) ? BSIZE_HEIGHT : 0;
	newPositionX += (newPositionX < 0) ? BSIZE_WIDTH : 0;  

	if(board[newPositionY][newPositionX]>=0){
		return 1;
	}else{
		return 0;
	}		
}
