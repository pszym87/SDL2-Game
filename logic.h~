#ifndef LOGIC_H
#define LOGIC_H
#define MV_UP			(index_t){-1,0}
#define MV_DOWN			(index_t){1,0}
#define MV_LEFT			(index_t){0,-1}
#define MV_RIGHT		(index_t){0,1}
#define BSIZE_HEIGHT		4
#define BSIZE_WIDTH		8		
#define MAX_SINGLE_PRIZE	4
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


/**
 * \brief Wykonaj ruch. Implementacja regul gry. 
 *
 * Glowna funkcja odpowiadajaca za reguly gry. Sluzy do wyprowadzenia ruchu dla kazdej figury.
 * Niezaleznie czy jest to ruch gracza (Mario) czy ruch przeciwnika (potworki). 
 * Funkcja sprawdza czy mozliwe jest wykonanie ruchu i uaktualnia plansze po wykonaniu ruchu. 
 * Jesli ruch jest wykonany uaktualniana jest pozycja figury podana w argumencie *currentPositionOfFigure
 * oraz na planszy gry podana w argumencie board.
 * 
 * \param positionChangeRequest intencja zmiany pozycji opisana jako koordynaty
 *	  x,y; dozwolony ruch o 1 w osi x lub y
 * \param *currentPositionOfFigure okreslenie ktorej figury dotyczy ruch
 * \param board Plansza gry. 
 */
void moveRespectingRules(index_t positionChangeRequest, index_t *currentPositionOfFigure, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);

/**
 * \brief Wygeneruj losowy wykonalny ruch dla podanej figury
 *
 * \param *currentPositionOfFigure biezaca pozycja figury
 * \param board Plansza ze stanem gry
 * \return Zwraca losowy ruch jako przemieszczenie wzgledne wyrazone wskaznikiem do index_t
 */

index_t generateRandomPossibleMove(index_t *currentPositionOfFigure, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);

/**
 * \brief Pomocnicza funkcja sprawdzajaca czy jednostkowy 
 * 	  ruch jest mozliwy do wykonania
 *
 * \param positionChangeRequest o ile zmienic pozycje
 * \board Plansza
 * \return 1 ruch mozliwy do wykonania, 0 ruch niemozliwy do wykonania
 */
int czyMozliwy(index_t positionChangeRequest, index_t*, int board[BSIZE_HEIGHT][BSIZE_WIDTH]);

#endif
