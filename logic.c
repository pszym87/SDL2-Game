#include "logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "adj.h"

void* genMovesForGhosts(void *arg){
	srand(time(0));
	
	game_t *myGame = (game_t*)arg;

	myGame->ghostNextMove[1] = genRandSilly(myGame->ghostIndex+1, myGame->board);
	myGame->ghostNextMove[2] = genRandFwd(*(myGame->ghostIndex+2), myGame->adj); 
	myGame->ghostNextMove[0] = genDij(myGame);
	
	return NULL;
}

void moveGhosts(game_t *myGame){
	execMoveGhost(myGame->ghostNextMove[0], myGame, 0);
	execMoveGhost(myGame->ghostNextMove[1], myGame, 1);
	execMoveGhost(myGame->ghostNextMove[2], myGame, 2);
}


void gameInit(game_t *myGame, int num){
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
	
	for(int i=0; i<myGame->ghost_num; i++)
		myGame->ghostNextMove[i] = (index_t){0,0};
	
	generateAdjMatrix(myGame->board,myGame->adj);
}


index_t genDij(game_t *myGame){
	// an auxiliary array will store predecessors for each node in the shortest path
	int prev[BSIZE_HEIGHT*BSIZE_WIDTH];  

	// find Mario in the graph
	int root = getVertex(myGame->marioIndex.y, myGame->marioIndex.x); 	
	
	// find the shortest path between the Mario's node and every other node in the graph
	dijkstra(myGame->adj, root, prev); 

	// find the ghost number 1 in the graph
	int ghost = getVertex(myGame->ghostIndex->y, myGame->ghostIndex->x);
	
	// by reading the predecessor of the ghost node, the next move of the ghost is determined 
	int ghost_prev = prev[ghost];
	
	// translate the graph node into matrix representation
	index_t new_coords = getBoardIndex(ghost_prev);
	
	// calculate new relative position on the board
	new_coords = (index_t) {new_coords.y - myGame->ghostIndex->y, new_coords.x - myGame->ghostIndex->x};

	return new_coords;	
		
}

void movePlayer(game_t *myGame){
	execMovePlayer(myGame);			
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
	
	//otherwise return erroreous value
	return (index_t){-1,-1};
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

void execMovePlayer(game_t *gm){

	// if someone has finished the game, exit the function
	if(gm->gameStatus == SSTOP) return;

	// (1) if the player doesn't want to change its position - do nothing
	// (2) process any other request of position change 
	if(!(gm->playerMove.x==0 && gm->playerMove.y==0)){

		// Make the move cyclical in two steps
		// (cyclical movements allow leaping from edges)
		
		// First step: convert coordinates, from relative to absolute
		int newPositionX = (gm->marioIndex.x + gm->playerMove.x);
		int newPositionY = (gm->marioIndex.y + gm->playerMove.y);

		// Second step: check consecutively top, left, bottom and right edge
		if(newPositionY < 0) newPositionY = BSIZE_HEIGHT-1;
		if(newPositionX < 0) newPositionX = BSIZE_WIDTH-1;
		if(newPositionY > BSIZE_HEIGHT-1) newPositionY = 0;
		if(newPositionX > BSIZE_WIDTH-1) newPositionX = 0; 

		// Check if the move is permissible
	
		// Moving around the walls it not possible
		if(gm->board[newPositionY][newPositionX]==B_WALL){

	        	;// ignore the move by doing nothing

		}
		// Any other move is permissible
		else{
			
			// If there is a collision between Mario and any of ghosts - STOP THE GAME - You have lost.
			if( ghostsMarioCollision((index_t){newPositionY, newPositionX},gm) ){
				gm->gameStatus = SSTOP;
			}	

			else{				
				// Apply the move to the board, if the field has a bonus, add it to Mario's score 
				int prize = consumeAndSwap(&gm->board[gm->marioIndex.y][gm->marioIndex.x],
					       &gm->board[newPositionY][newPositionX]);
					
			}
			
			// update Mario's position in the main struct
			gm->marioIndex.x = newPositionX;
			gm->marioIndex.y = newPositionY;
		}
	}

}

void execMoveGhost(index_t relPosReq, game_t *gm, int num){

	// if someone has finished the game, exit the function
	if(gm->gameStatus == SSTOP) return;
	
	// Make the move cyclical in two steps
	// (cyclical movements allow leaping from edges)

	// First step: convert coordinates, from relative to absolute
        int newPositionX = (gm->ghostIndex[num].x + relPosReq.x);
	int newPositionY = (gm->ghostIndex[num].y + relPosReq.y);
	
	// Second step: check consecutively top, left, bottom and right edge
	if(newPositionY < 0) newPositionY = BSIZE_HEIGHT-1;
	if(newPositionX < 0) newPositionX = BSIZE_WIDTH-1;
	if(newPositionY > BSIZE_HEIGHT-1) newPositionY = 0;
	if(newPositionX > BSIZE_WIDTH-1) newPositionX = 0; 

	// Check if the move is permissible

	// Moving around the walls it not possible
	if(gm->board[newPositionY][newPositionX] == B_WALL){

        	;// ignore the move by doing nothing

	// Any other move is permissible
	}else{				

		// If there is a collision between Mario and any of ghosts - STOP THE GAME - You have lost.
		if( marioGhostsCollision((index_t){newPositionY, newPositionX},gm) ){
				gm->gameStatus = SSTOP;
		
		// Otherwise, move the figure to the requested position
		}else{

			// apply the move to the board
			swap(&gm->board[gm->ghostIndex[num].y][gm->ghostIndex[num].x],&gm->board[newPositionY][newPositionX]);
		
		}	
		// update figure's position in the main struct
		gm->ghostIndex[num].x = newPositionX;
		gm->ghostIndex[num].y = newPositionY;
	}
}

index_t genRandSilly(const index_t *currPos,int board[BSIZE_HEIGHT][BSIZE_WIDTH]){

	// counter of permissible moves
	int count_perm = 0;

	index_t mv_arr[] = {MV_UP, MV_DOWN, MV_LEFT, MV_RIGHT};
	
	// setting up lists
	// -- 'current_node' is used for traversing through the list	
	mv_list_t *head, *current_node;
	head = malloc(sizeof(mv_list_t));
	head->next = NULL;	
	current_node = head;

	// generate a list of all permissible moves for a given position
	for(int i=0; i<sizeof mv_arr/sizeof(index_t); i++){
		 
		if(isPossible(mv_arr[i], currPos, board)){
			
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
 
	// translate matrix position to the graph node index
	int curr_vrtx = getVertex(curr_pos.y, curr_pos.x); 	

	queue_t *neighb_q = create_queue();	
	int q_size = 0;

	// add all adjacent vertexex to the queue
	for(int i=0; i<size; i++)
		if(graph[curr_vrtx][i] == 1 && i!=rec_visited){
			push_q(neighb_q, i);
			++q_size;
		}

	// allow a backward move if other options aren't available
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

int isPossible(index_t positionChangeRequest, const index_t *currentPositionOfFigure, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
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
