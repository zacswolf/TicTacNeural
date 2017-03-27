// Copyright 2017 Zac Schulwolf

#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_
#include <iostream>
#include <string>
#include <array>
#include <cmath>

#define BOARDSIZE 9

namespace tictac {

namespace tile {
typedef enum {
    EMPTY = 0, PLAYER1 = 1, PLAYER2 = 2
} tile;
}

namespace winner {
typedef enum {
    NOTFINISHED = 4, TIE = 3, PLAYER1 = 1, PLAYER2 = 2
} winner;
}

class Board {
 private:
    std::array<tile::tile, BOARDSIZE> data;
 public:
    Board();
    bool set(size_t location, tile::tile player);  // true if successful
    tile::tile get(size_t location);
    bool isEmpty(size_t location);  // true if empty; false if taken
    void clear();
    size_t size() {
        return BOARDSIZE;
    }
    std::string toString();
    winner::winner checkForWinner();
};
}

#endif  // SRC_BOARD_H_
