// Copyright 2017 Zac Schulwolf

#include "game.h"

namespace tictac {
Game::Game() {
    whoseTurn = player::PLAYER1;
    numTurns = 0;
    numRounds = 1;
    theWinner = winner::NOTFINISHED;
    started = player::PLAYER1;
    myBoard = new Board();
}
Game::~Game() {
	delete myBoard;
}

void Game::start() {
	doTurn();
}

void Game::newRound() {
    numRounds++;
    myBoard->clear();
    whoseTurn = static_cast<player::player>(whoseTurn % 2 + 1);
    if (theWinner == player::PLAYER1 || theWinner == player::PLAYER2) {
        // player won
        started = static_cast<player::player>(theWinner);
    } else {
        // tie, switch first turn
        started = whoseTurn;
    }
    doTurn();
}
void Game::doTurn() {
    numTurns++;
    std::string choice;
    std::cout << "Input for " << this->whoseTurn << ": ";
    std::cin >> choice;
    while (!(myBoard->set(static_cast<position::position>(std::stoi(choice)), static_cast<tile::tile>(whoseTurn) ))) {
    	std::cout << "Invalid Input! " << std::endl;
    	std::cout << "Input for " << this->whoseTurn << ": ";
        std::cin >> choice;
    }
    whoseTurn = static_cast<player::player>(whoseTurn % 2 + 1);
    theWinner = myBoard->checkForWinner();
    if (theWinner == winner::NOTFINISHED) {
        // round is not finished
        std::cout << myBoard->toString() << std::endl;
        doTurn();
    } else {
        // round is over
        std::cout << "winner: " << theWinner << std::endl;
        std::cout << myBoard->toString() << std::endl;
        newRound();  // never terminates
    }
}
size_t Game::turnNum() {
    return numTurns;
}
size_t Game::roundNum() {
    return numRounds;
}
}
