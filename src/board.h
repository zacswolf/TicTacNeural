#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string>
#include <array>
#include <math.h> 

#define BOARDSIZE 9

namespace T
{
    typedef enum {
        EMPTY=0, PLAYER1=1, PLAYER2=2
    } tile;
}

namespace W
{
    typedef enum {
        NOTFINISHED=4, TIE=3, PLAYER1=1, PLAYER2=2
    } winner;
}
    
class Board {
  private:
    std::array<T::tile, BOARDSIZE> data;
  public:
  	Board();
    bool set(int location, T::tile player); // true if successful
    T::tile get(int location);
	bool isEmpty(int location); // true if empty; false if taken
	void clear();
	int size() {
		return BOARDSIZE;
	}
	std::string toString();
    W::winner checkForWinner();
	
};






#endif 		//BOARD_H
