// Copyright 2017 Zac Schulwolf

#include "board.h"

Board::Board() {
    data.fill(T::EMPTY);
}

bool Board::set(int location, T::tile player) {
    if (data[location] == T::EMPTY) {
        data[location] = player;
        return true;
    } else {
        return false;
    }
}

T::tile Board::get(int location) {
    return data[location];
}
bool Board::isEmpty(int location) {
    return data[location] == T::EMPTY;
}
void Board::clear() {
    data.fill(T::EMPTY);
}

std::string Board::toString() {
    std::string ret = "";
    int i = 0;
    for (int a=0; a < sqrt(size()); a++) {
        for (int b=0; b < sqrt(size()); b++) {
            ret += std::to_string(data[i]);
            ret += ", ";
            i++;
        }
    ret+= "\n";
    }
    return ret;
}

W::winner Board::checkForWinner() {
    if (((data[4] == data[0] && data[4] == data[8]) || (data[4] == data[2] && data[4] == data[6]) || (data[4] == data[3] && data[4] == data[5]) ||
        (data[4] == data[1] && data[4] == data[7])) && (data[4] != T::EMPTY)) {
        // center tile
        // diag, diag, hor, vert
        std::cout << "winner case 1\n";
        return static_cast<W::winner>(data[4]);
    } else if (((data[0] == data[1] && data[0] == data[2]) || (data[0] == data[3] && data[0] == data[6])) && (data[0] != T::EMPTY)) {
        // top-left tile
        // hor, vert
        std::cout << "winner case 2\n";
        return static_cast<W::winner>(data[0]);
    } else if (((data[8] == data[7] && data[8] == data[6]) || (data[8] == data[5] && data[8] == data[2])) && (data[8] != T::EMPTY)) {
        // bottom-right tile
        // hor, vert
        std::cout << "winner case 3\n";
        return static_cast<W::winner>(data[8]);
    } else if (!((data[0] == T::EMPTY) || (data[1] == T::EMPTY) || (data[2] == T::EMPTY) || (data[3] == T::EMPTY) ||
        (data[4] == T::EMPTY) || (data[5] == T::EMPTY) || (data[6] == T::EMPTY) || (data[7] == T::EMPTY) || (data[8] == T::EMPTY))) {
        // TIE
        return W::TIE;
    } else {
        // No winner
        return W::NOTFINISHED;
    }
}
