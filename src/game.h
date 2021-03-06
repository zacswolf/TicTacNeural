// Copyright 2017 Zac Schulwolf

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "board.h"
#include "net/src/network.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

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
    network::Network* ai;
    bool isAI;
    player::player whoseTurn;
    size_t numTurns;
    size_t numRounds;
    int lastMove;
    winner::winner theWinner;
    player::player started;  // the player with the first turn of the round
    Board* myBoard;
    std::ofstream csv; // csv file that we are recording to in this game
 public:
    Game();
    Game(std::string);
    ~Game();
    void start();
    void newRound();
    std::vector<size_t> getBoardState();
    void doTurn();
    void doPlayerTurn();
    void doAITurn();
    size_t turnNum();
    size_t roundNum();
    void endGame();
    bool tryToPlay(int i);
};
}

#endif  // SRC_GAME_H_
