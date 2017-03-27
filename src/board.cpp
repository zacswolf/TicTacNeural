// Copyright 2017 Zac Schulwolf

#include "board.h"

#include <sstream>

namespace tictac {
Board::Board() {
    data.fill(tile::EMPTY);
}

bool Board::set(size_t location, tile::tile player) {
    if (data[location] == tile::EMPTY) {
        data[location] = player;
        return true;
    } else {
        return false;
    }
}

tile::tile Board::get(size_t location) {
    return data[location];
}
bool Board::isEmpty(size_t location) {
    return data[location] == tile::EMPTY;
}
void Board::clear() {
    data.fill(tile::EMPTY);
}

std::string Board::toString() {
    std::stringstream ret;
    size_t i = 0;
    for (size_t a=0; a < std::sqrt(size()); a++) {
        for (size_t b=0; b < std::sqrt(size()); b++) {
            ret << std::to_string(data[i]);
            ret << " ";
            i++;
        }
    ret << "\n";
    }
    return ret.str();
}

winner::winner Board::checkForWinner() {
    if (((data[4] == data[0] && data[4] == data[8]) || (data[4] == data[2] && data[4] == data[6]) || (data[4] == data[3] && data[4] == data[5]) ||
        (data[4] == data[1] && data[4] == data[7])) && (data[4] != tile::EMPTY)) {
        // center tile
        // diag, diag, hor, vert
        // std::cout << "Winner case 1" << std::endl;
        return static_cast<winner::winner>(data[4]);
    } else if (((data[0] == data[1] && data[0] == data[2]) || (data[0] == data[3] && data[0] == data[6])) && (data[0] != tile::EMPTY)) {
        // top-left tile
        // hor, vert
        // std::cout << "Winner case 2" << std::endl;
        return static_cast<winner::winner>(data[0]);
    } else if (((data[8] == data[7] && data[8] == data[6]) || (data[8] == data[5] && data[8] == data[2])) && (data[8] != tile::EMPTY)) {
        // bottom-right tile
        // hor, vert
        // std::cout << "Winner case 3" << std::endl;
        return static_cast<winner::winner>(data[8]);
    } else if (!((data[0] == tile::EMPTY) || (data[1] == tile::EMPTY) || (data[2] == tile::EMPTY) || (data[3] == tile::EMPTY) ||
        (data[4] == tile::EMPTY) || (data[5] == tile::EMPTY) || (data[6] == tile::EMPTY) || (data[7] == tile::EMPTY) || (data[8] == tile::EMPTY))) {
        // TIE
        return winner::TIE;
    } else {
        // No winner
        return winner::NOTFINISHED;
    }
}
}
