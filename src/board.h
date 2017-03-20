#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string>
#include <array>

#define BOARDSIZE 9

typedef enum {
	EMPTY, PLAYER1=1, PLAYER2=2
} tile;

typedef enum {
	NOTFINISHED, TIE, PLAYER1=1, PLAYER2=2
} winner;

class Board {
  private:
	std::array<tile, BOARDSIZE> data;
  public:
  	Board();
    void set(int location, tile player);
	tile get(int location);
	bool isEmpty(int location); // if empty, true; if taken, false
	void clear();
	tile* readAll();
	int size() {
		return BOARDSIZE;
	}
	std::string toString();
	winner checkForWinner();
	
};






#endif 		//BOARD_H