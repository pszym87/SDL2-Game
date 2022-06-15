#include "stdio.h"
#include "stdlib.h"

#define BSIZE_HEIGHT		4
#define BSIZE_WIDTH		8		
#define MV_UP			{-1,0}
#define MV_DOWN			{1,0}
#define MV_LEFT			{0,-1}
#define MV_RIGHT		{0,1}
#define MAX_SINGLE_PRIZE	4
#define ASC_UP			'i'
#define ASC_DOWN		'k'
#define ASC_LEFT		'j'
#define ASC_RIGHT		'l'


// KOMENTARZ #1
// chcialbym to jeszcze zakodowac na wskaznikach wielowymiarowych (podwojnych) - zeby to sobie dobrze przecwiczyc

// KOMENTAZR #2
// chcialbym to jeszcze zakodowac z uzyciem wyrazenia regularnego ? (expression)
// nie mozna miec w ternary operatorze returna

struct index{
	int y;
	int x;
};

typedef struct index Index;

int swap(int*, int*);
int consumeAndSwap(int*, int*);
void printTheBoard(int[BSIZE_HEIGHT][BSIZE_WIDTH]);
Index getAnIndexPositionOf(int, int[BSIZE_HEIGHT][BSIZE_WIDTH]);
void printIndexPosition(Index);
void moveRespectingRules(Index, Index*, int[BSIZE_HEIGHT][BSIZE_WIDTH]);
Index generateRandomPossibleMove(Index*, int[BSIZE_HEIGHT][BSIZE_WIDTH]);
int czyMozliwy(Index, Index*, int[BSIZE_HEIGHT][BSIZE_WIDTH]);
void twoPlayersPlay(Index*, Index*, int[BSIZE_HEIGHT][BSIZE_WIDTH]);
void onePlayerPlay(Index*, Index*, int[BSIZE_HEIGHT][BSIZE_WIDTH]);

int main(){
	
	int board[BSIZE_HEIGHT][BSIZE_WIDTH] = {
	{ -1 ,  1 ,  10, -1 , 1 , 1 , 1 , 1 }, 
	{  1 , -1 ,  1 , -1 , 1 , -1,-1 , 1 }, 
	{  4 ,  1 ,  1 ,  1 ,-1 , 1 , 1 , 1 },
	{  0 , -1 , -1 , -1 , 1 , -1, -1, 1 }
	};

	Index marioIndex = getAnIndexPositionOf(10,board);
	Index ghostIndex = getAnIndexPositionOf(4,board);
	printIndexPosition(marioIndex);
	printIndexPosition(ghostIndex);
	printTheBoard(board);
	//swap(&board[0][0], &board[3][0]);
	//printTheBoard(board);
	//consumeAndSwap(&board[0][2], &board[1][2]);
	
	// petla sterujaca
	
	//moveRespectingRules((struct index)MV_DOWN, &marioIndex, board);
	//moveRespectingRules((struct index)MV_RIGHT, &ghostIndex, board);
	//printIndexPosition(marioIndex);
	//printIndexPosition(ghostIndex);
	//printTheBoard(board);
	
	onePlayerPlay(&marioIndex, &ghostIndex, board);
}

/*
 *
*/ 
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

void printTheBoard(int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	
	printf("\n\n=== The board ===\n\n"); 	

	for(int i=0; i<BSIZE_HEIGHT; i++){
		for(int j=0; j<BSIZE_WIDTH; j++){
			printf("%3d\t", board[i][j]);
		} 
		printf("\n");
	}

}


Index getAnIndexPositionOf(int value, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	for(int i=0; i<BSIZE_HEIGHT; i++)
		for(int j=0; j<BSIZE_WIDTH; j++)
			if(value == board[i][j]){
				 return (Index){i,j};  		
			}			
}

void printIndexPosition(Index position){
	printf("\nIndex position y=%d, x=%d\n", position.y, position.x);
}

void moveRespectingRules(Index positionChangeRequest, Index *currentPositionOfFigure, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	// normalizuj ruch; pozwala na wykonywanie ruchow z ostatniego indeksu do pierwszego
	// jesli znajduje sie przejscie
	int newPositionX = (currentPositionOfFigure->x + positionChangeRequest.x);
	int newPositionY = (currentPositionOfFigure->y + positionChangeRequest.y);
	
	newPositionY += (newPositionY < 0) ? BSIZE_HEIGHT : 0;
	newPositionX += (newPositionX < 0) ? BSIZE_WIDTH : 0;  

	printf("\nRequest dla pozycji:y=%d x=%d", newPositionY, newPositionX);
	// sprawdza czy ruch jest mozliwy do wykonania na boardzie (czy nie ma sciany)
	if(board[newPositionY][newPositionX]>=0){
		// jesli pacman
		if(board[currentPositionOfFigure->y][currentPositionOfFigure->x] > MAX_SINGLE_PRIZE){
			//zamien pozycjami pacmana z "nagroda"
			printf("** ruch mario o x=%d y=%d **", positionChangeRequest.x, positionChangeRequest.y);
			int prize = consumeAndSwap(&board[currentPositionOfFigure->y][currentPositionOfFigure->x],
				       &board[newPositionY][newPositionX]);
			if(prize>14)
				printf("\nYOU KINDA WIN\n");
			 	
		}	
		else{ // jesli potworek
			printf("** ruch potworka o x=%d y=%d **", positionChangeRequest.x, positionChangeRequest.y);
			int prize = swap(&board[currentPositionOfFigure->y][currentPositionOfFigure->x],
			     &board[newPositionY][newPositionX]);
			if(prize>=14)
				printf("\nYOU LOSE!\n");

		}
		//zaktualizuj koordynaty figury 
		currentPositionOfFigure->x = newPositionX;
		currentPositionOfFigure->y = newPositionY;
	}

}

Index generateRandomPossibleMove(Index *currentPositionOfFigure,int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	// lista
	struct lista{
		Index position;
		struct lista *l;
	};

	int ileMozliwych = 0;

	Index array[4] = {(Index)MV_UP, (Index)MV_DOWN, (Index) MV_LEFT, (Index) MV_RIGHT};
	
	struct lista head = {(Index){0,0}, NULL};
	struct lista *ptr_element = &head;

	for(int i=0; i<4; i++){
		// na tym przykladzie musisz zrozumiec jak dziala zakres zmiennych
		// i odwolanie przez referencje! 
		struct lista *temp = malloc(sizeof(struct lista));
		temp->position = array[i];
		temp->l =  NULL;
		
		if(czyMozliwy(array[i], currentPositionOfFigure, board)){
			ptr_element->l = temp;
			++ileMozliwych;
			ptr_element = temp;
			printf("Znalazlem mozliwosc x=%d y=%d\n", temp->position.x, temp->position.y);
		}
		free(temp); // dlaczego to dziala? trzeba po prostu lepiej znaznajomic sie z tym co robi malloc i free. 
	}	
	
	int los = rand() % ileMozliwych;
	++los;

	ptr_element = &head;
	while(los>0){
		
		ptr_element = ptr_element->l;
		--los;
		//free(temp); <-- nie mam pojecia jak wyczyscic po sobie
	}

	return ptr_element->position;

}	

int czyMozliwy(Index positionChangeRequest, Index *currentPositionOfFigure, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
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

void twoPlayersPlay(Index *marioIndex, Index *ghostIndex, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){

	char c;
	Index move;
	int zmianaFigury = 0;
	while(c!='q'){
		printf("Wprowadz ruch dla %s\n", (zmianaFigury%2 == 0) ? "Mario" : "Duszka");
		scanf("%c", &c);
		switch(c){
			case ASC_UP:
				move = (Index) MV_UP;
				break;

			case ASC_DOWN:
				move = (Index) MV_DOWN;
				break;
			case ASC_LEFT:
				move = (Index) MV_LEFT;
				break;

			case ASC_RIGHT:
				move = (Index) MV_RIGHT;
				break;
		}
		if(zmianaFigury++%2 == 0){
			printf("Ruch Mario: \n");
			moveRespectingRules(move, marioIndex, board);
		} else{
			printf("Ruch Duszka: \n");
			moveRespectingRules(move, ghostIndex, board);
		}
		
		printTheBoard(board);
		scanf("%c", &c);
		printf("Nacisnieto: %c", c);
	
	}
}

void onePlayerPlay(Index *marioIndex, Index *ghostIndex, int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
		
	char c;
	Index move;
	int zmianaFigury = 0;

	while(c!='q'){
		if(zmianaFigury%2 == 0){
			printf("Wprowadz ruch dla Mario:\n");
			scanf("%c", &c);
			fflush(stdin);
			zmianaFigury++;
			switch(c){
				case ASC_UP:
					move = (Index) MV_UP;
					break;

				case ASC_DOWN:
					move = (Index) MV_DOWN;
					break;
				case ASC_LEFT:
					move = (Index) MV_LEFT;
					break;

				case ASC_RIGHT:
					move = (Index) MV_RIGHT;
					break;
			}
			moveRespectingRules(move, marioIndex, board);
		}else{
			zmianaFigury++;
			move = generateRandomPossibleMove(ghostIndex, board);
			moveRespectingRules(move, ghostIndex, board);
		}
	printTheBoard(board);
	}		
}
