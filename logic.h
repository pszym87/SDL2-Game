#include <stdbool.h> 

#ifndef LOGIC_H
#define LOGIC_H
#define MV_UP			(index_t){-1,0}
#define MV_DOWN			(index_t){1,0}
#define MV_LEFT			(index_t){0,-1}
#define MV_RIGHT		(index_t){0,1}
#define BSIZE_HEIGHT		27
#define BSIZE_WIDTH		18		
#define MAX_SINGLE_PRIZE	4
#define SPLAY			1
#define SPAUSE			2
#define SSTOP			0
#define SINTRO			4
#define KEYB_LEN		350
#define NGHOSTS			3
#define B_WALL			-1


/**
 * \file logic.h
 * \brief Zbior elementow odpowiadajacych
	  za logike gry
 */
/**
 * \def MV_UP
 * \brief Ruch w gore wyrazony jako koordynaty x,y. Celem czytelnosci kodu przerzutowane od razu
 *        do typu index_t 

 * \def MV_DOWN
 * \brief Ruch w dol wyrazony jako koordynaty x,y. Celem czytelnosci kodu przerzutowane od razu
 *        do typu index_t 

 * \def MV_LEFT
 * \brief Ruch w lewo wyrazony jako koordynaty x,y. Celem czytelnosci kodu przerzutowane od razu
 *        do typu index_t 

 * \def MV_RIGHT
 * \brief Ruch w gore wyrazony jako koordynaty x,y. Celem czytelnosci kodu przerzutowane od razu
 *        do typu index_t 

 * \def BSIZE_HEIGHT 
 * \brief Wysokosc planszy (wiersze)

 * \def BSIZE_WIDTH 
 * \brief Szerokosc planszy (kolumny)

 * \def MAX_SINGLE_PRIZE
 * \brief Maksymalna wartosc punktowa figury (jaka jest maksymalna nagroda za potworka)
 */

/**
 * \typedef index_t
 * 
 * \brief Koordynaty x,y sluzace do okreslenia pozycji figury na mapie
 * 
 * \var int y
 * \brief wiersze
 * 
 * var int x
 * \brief kolumny
 * 
 */
typedef struct index{
	int y;
	int x;
} index_t;



/** \typedef mv_list_t
 *  
 * \brief Linked list of moves
 */
typedef struct mv_list_s mv_list_t;

struct mv_list_s{
	index_t position;
	mv_list_t *next;
};
/**
 * \brief The main structure of a game. 
 */
typedef struct game{
	int board[BSIZE_HEIGHT][BSIZE_WIDTH]; /** The map represented as a 2D matrix. Holds information about points for each field.  */
	index_t marioIndex;		/**< Store a current position of Mario */
	index_t	*ghostIndex;		/**< Stores a current position of each ghost */
	index_t ghostNextMove[NGHOSTS]; /**< Stores a next move for each ghost*/
	int ghost_num;
	int gameStatus;
	int keyb[KEYB_LEN];
	index_t playerMove;
	int adj[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH]; /** The map as an adjacency matrix. It shows only routes and hides the rest information */
} game_t;

/** \brief Generates moves for ghosts. 
 * 
 * A standarization of the function was needed in order to use pthread. Thus the function returns a void pointer and takes a void pointer as
 * an argument. The new move is not applied to the map it is stored in the game_t structure in the array 'ghostNextMove()'.
 * Use the moveGhosts() function to write a move into the map. 
 * 
 * \param arg Pass a pointer to the game_t structure here 
 *
 */
void* genMovesForGhosts(void *arg);

/** \brief Generates a move for the ghost number 1 using the Dijkstra algorithm. Move isn't written into the map.
 * 
 * \param myGame
 * \return Coordinates that are relative to the previous position of the ghost.  
 */
index_t genDij(game_t *myGame);

/** 
 * \brief Writes moves stored in the 'ghostNextMove' array into the map. 
 */
void moveGhosts(game_t *myGame);

/* \fn genRandFwd()
 * \brief Random move forward(no returns to the previous position)
 * Random move with the following algoritm
 * 1. Queue all adjacent nodes of the current node (exclude recently visited nodes)
 * 2. If there are no adjacent nodes not recently visited, add previously visited node to the queue 
 * 3. Draw a move from the queue
 * 4. Set current move as recently visited
 * 
 * \param curr_pos Current position of the figure
 * \param graph The adjacency matrix of the graph that represents a game map
 * \return Move for the figure (expressed as relative index position)
 */
index_t genRandFwd(index_t curr_pos, int graph[BSIZE_HEIGHT*BSIZE_WIDTH][BSIZE_HEIGHT*BSIZE_WIDTH]);

void movePlayer(game_t *myGame);
void gameInit(game_t *myGame, int num);

/**
 * \brief Ta funkcja przesuwaja sie potworki
 *
 * Funkcja jest uzywana do zamiany miejsc na mapie.
 * Sluzy w programie do przemieszczania sie figur po
 * mapie (domyslnie uzywana dla potworkow)
 *
 * \param *miejsce1 
 * \param *miejsce2
 * \return Zwraca sume elementow bioracych udzial w "transakcji"
 */
int swap(int *miejsce1, int *miejsce2);

/**
 * \brief Ta funkcja sluzy do przesuwania sie Mario
 * 
 * Funkcja sluzy do przesuwania sie Mario po mapie. Logika
 * jest nastepujaca: punkty sumuja sie i zapisuja w jednej zmiennej
 * podczas gdy w drugiej zapisuje sie 0.  
 * 
 * \param *miejsce1 
 * \param *miejsce2

 * \return Zwraca sume elementow bioracych udzial w "transakcji" 
 */
int consumeAndSwap(int *miejsce1, int *miejsce2);

/**
 * \brief Podaje koordynaty szukanej figury na mapie
 * 
 * \param value Wartosc figury
 * \param board Plansza reprezentujaca stan gry
 * 
 * \return Pozycja odnalezionej figury wyrazona jako x,y
 */
index_t getAnIndexPositionOf(int value, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);


bool ghostsMarioCollision(index_t p, game_t *gm);
bool marioGhostsCollision(index_t p, game_t *gm);
/**
 * \brief Wykonaj ruch Mario. Testowa implementacja. 
 *
 * Glowna funkcja odpowiadajaca za reguly gry dla Mario. 
 * Funkcja sprawdza czy mozliwe jest wykonanie ruchu i uaktualnia plansze po wykonaniu ruchu. 
 * Jesli ruch jest wykonany uaktualniana jest pozycja figury podana w argumencie *currentPositionOfFigure
 * oraz na planszy gry podana w argumencie board.
 * Po ruchu aktualizowana jest flaga gry (sukces, porazka lub bez zmian)
 
 * \param positionChangeRequest intencja zmiany pozycji opisana jako koordynaty
 *	  x,y; dozwolony ruch o 1 w osi x lub y
 * \param *gm Wskaznik do struktury gry  */
void execMovePlayer(game_t *gm);
/**
 * \brief Wykonaj ruch. Implementacja regul gry. 
 *
 * Glowna funkcja odpowiadajaca za reguly gry. Sluzy do wyprowadzenia ruchu dla kazdej figury.
 * Niezaleznie czy jest to ruch gracza (Mario) czy ruch przeciwnika (potworki). 
 * Funkcja sprawdza czy mozliwe jest wykonanie ruchu i uaktualnia plansze po wykonaniu ruchu. 
 * Jesli ruch jest wykonany uaktualniana jest pozycja figury podana w argumencie *currentPositionOfFigure
 * oraz na planszy gry podana w argumencie board.
 * 
 * \param relPosReq intencja zmiany pozycji opisana jako koordynaty
 *	  x,y; dozwolony ruch o 1 w osi x lub y
 * \param *currentPositionOfFigure okreslenie ktorej figury dotyczy ruch
 * \param board Plansza gry. 
 */
void execMoveGhost(index_t relPosReq, game_t *gm, int num);

/** \fn generateRandomPossibleMove
 * \brief Drawes a random but permissible move for a given position
 *
 * \param *currentPositionOfFigure given position
 * \param board board of the game
 * \return drawn move for the figure
 */

index_t genRandSilly(const index_t *currPos, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);

/**
 * \brief Pomocnicza funkcja sprawdzajaca czy jednostkowy 
 * 	  ruch jest mozliwy do wykonania
 *
 * \param positionChangeRequest o ile zmienic pozycje
 * \board Plansza
 * \return 1 ruch mozliwy do wykonania, 0 ruch niemozliwy do wykonania
 */
int isPossible(index_t positionChangeRequest, const index_t*, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);

#endif
