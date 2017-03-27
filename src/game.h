// Copyright 2017 Zac Schulwolf

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "board.h"

#include <string>
#include <iostream>

namespace Pos {
    typedef enum {
        TOPLEFT    = 0, TOPMIDDLE    = 1, TOPRIGHT    = 2,
        MIDDLELEFT = 3, MIDDLE       = 4, MIDDLERIGHT = 5,
        BOTTOMLEFT = 6, BOTTOMMIDDLE = 7, BOTTOMRIGHT = 8
    } position;
}


namespace Play {
    typedef enum {
        PLAYER1 = 1, PLAYER2 = 2, NONE = 0
    } player;
}

class Game {
 private:
    Play::player whoseTurn;
    int numTerms;
    int numRounds;
    W::winner theWinner;
    Play::player started;  // the player with the first term of the round
    Board* myBoard;
 public:
    Game();
    void newRound();
    void turn();
    int turnNum();
    int roundNum();
};




#endif  // SRC_GAME_H_
