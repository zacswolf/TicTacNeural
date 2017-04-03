// Copyright 2017 Zac Schulwolf

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "board.h"

#include <string>
#include <iostream>
#include <fstream>

namespace tictac {

namespace position {
typedef enum {
    TOPLEFT    = 0, TOPMIDDLE    = 1, TOPRIGHT    = 2,
    MIDDLELEFT = 3, MIDDLE       = 4, MIDDLERIGHT = 5,
    BOTTOMLEFT = 6, BOTTOMMIDDLE = 7, BOTTOMRIGHT = 8
} position;
}

namespace player {
typedef enum {
    NONE = 0, PLAYER1 = 1, PLAYER2 = 2
} player;
}

class Game {
 private:
    player::player whoseTurn;
    size_t numTurns;
    size_t numRounds;
    winner::winner theWinner;
    player::player started;  // the player with the first turn of the round
    Board* myBoard;
    std::ofstream csv; // csv file that we are recording to in this game
 public:
    Game();
    ~Game();
    void start();
    void newRound();
    void doTurn();
    size_t turnNum();
    size_t roundNum();
    void endGame();
};
}

#endif  // SRC_GAME_H_
