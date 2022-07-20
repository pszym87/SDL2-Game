#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
 
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


void moveRespectingRules_new(index_t positionChangeRequest, game_t *gm){

	if(!(positionChangeRequest.x==0 && positionChangeRequest.y==0)){
		// Zmienia tablice w poniekad liste cykliczna
		// Pozwala to na wykonanie skokow figury z ostatniego indeksu do pierwszego i na odwrot

		int newPositionX = (gm->marioIndex.x + positionChangeRequest.x);
		int newPositionY = (gm->marioIndex.y + positionChangeRequest.y);
		
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
			
			if(newPositionY == gm->ghostIndex.y && newPositionX == gm->ghostIndex.x){
				gm->gameStatus = SSTOP;
			}	

			else{
				//zamien pozycjami pacmana z "nagroda"
				printf("** ruch mario o x=%d y=%d **", positionChangeRequest.x, positionChangeRequest.y);
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

void moveRespectingRules(index_t positionChangeRequest, game_t *gm){

	// Zmienia tablice w poniekad liste cykliczna
        // Pozwala to na wykonanie skokow figury z ostatniego indeksu do pierwszego i na odwrot

        int newPositionX = (gm->ghostIndex.x + positionChangeRequest.x);
	int newPositionY = (gm->ghostIndex.y + positionChangeRequest.y);
	
	if(newPositionY < 0) newPositionY = BSIZE_HEIGHT-1;
	if(newPositionX < 0) newPositionX = BSIZE_WIDTH-1;
	  
	if(newPositionY > BSIZE_HEIGHT-1) newPositionY = 0;
	if(newPositionX > BSIZE_WIDTH-1) newPositionX = 0; 

	printf("\nRequest dla pozycji:y=%d x=%d", newPositionY, newPositionX);
	// sprawdza czy ruch jest mozliwy do wykonania na boardzie (czy nie ma sciany)
	if(gm->board[newPositionY][newPositionX]==-1){
        	// do nothing
	}else if(gm->board[newPositionY][newPositionX]>=0){				
		if(newPositionY==gm->marioIndex.y && newPositionX==gm->marioIndex.x){
				printf("You LOOSE!\n");
				gm->gameStatus = SSTOP;
		}else{
		printf("** ruch potworka o x=%d y=%d **", positionChangeRequest.x, positionChangeRequest.y);
		swap(&gm->board[gm->ghostIndex.y][gm->ghostIndex.x],&gm->board[newPositionY][newPositionX]);
		gm->ghostIndex.x = newPositionX;
		gm->ghostIndex.y = newPositionY;
		}	
	}
	
	//zaktualizuj koordynaty figury 
}

index_t generateRandomPossibleMove(index_t *currentPositionOfFigure,int board[BSIZE_HEIGHT][BSIZE_WIDTH]){
	// lista
	struct lista{
		index_t position;
		struct lista *l;
	};

	int ileMozliwych = 0;

	index_t array[4] = {MV_UP, MV_DOWN, MV_LEFT, MV_RIGHT};
	
	// ustaw wartownik listy	
	struct lista *head,*ptr_element;
	head = malloc(sizeof(struct lista));
	head->l = NULL;	
	
	ptr_element = head;
	// przejdz po elementach i zapisz w liscie wszystkie mozliwe
	// do wykonania ruchy
	for(int i=0; i<4; i++){
		 
		// sprawdza i-ty ruch z tablicy jest 
		// mozliwy do wykonania w obecnym stanie planszy
		if(czyMozliwy(array[i], currentPositionOfFigure, board)){
			struct lista *temp = malloc(sizeof(struct lista));
			temp->position = array[i];
			temp->l =  NULL;
			ptr_element->l = temp;
			++ileMozliwych;
			ptr_element = temp;
			printf("Znalazlem mozliwosc x=%d y=%d\n", temp->position.x, temp->position.y);
		} 
	}	
	
	// wylosuj, ktory z dostepnych ruchow zagrac
	int los = rand() % ileMozliwych; 
	printf("Wylosowano %d\n", los);
	++los;

	// przejdz po liscie aby wybrac wylosowany ruch
	ptr_element = head;
	while(los>0){
		
		printf("ptr_element: x=%d y=%d\n", ptr_element->l->position.x, ptr_element->l->position.y);
		ptr_element = ptr_element->l;
		--los;
	}

	// zwolnij zaalokowna pamiec	
	index_t ret = ptr_element->position;
	int i=0;	
	ptr_element = head;	
	while(ptr_element != NULL){
		printf("Iteracja #%d\n", i);
		struct lista *tmp = ptr_element;
		ptr_element = ptr_element->l;
		printf("Zwalniam: x=%d, y=%d", tmp->position.x, tmp->position.y);
		free(tmp);
		printf("\t Zwolniono\n");
		i++;
	}

		
	printf("Zaproponuje ruch x= %d, y=%d\n", ret.x, ret.y);
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
