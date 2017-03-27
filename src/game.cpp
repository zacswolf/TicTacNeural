#include "game.h"

Game::Game(){
    whoseTurn = Play::PLAYER1;
    numTerms = 0;
    numRounds = 1;
    theWinner = W::NOTFINISHED;
    started = Play::PLAYER1;
    myBoard = new Board();
    turn();
}

void Game::newRound(){
    numRounds++;
    myBoard->clear();
    whoseTurn = static_cast<Play::player>(whoseTurn % 2 + 1);
    if (theWinner == Play::PLAYER1 || theWinner == Play::PLAYER2) {
        // player won
        started = static_cast<Play::player>(theWinner);
    } else {
        // tie, switch first turn
        started = whoseTurn;
    }
    turn();
}
void Game::turn(){
    numTerms++;
    int choice;
    std::cin >> choice;
    while (!(myBoard->set(static_cast<Pos::position>(choice), static_cast<T::tile>(whoseTurn)))) {
        std::cin >> choice;
    }
    
    whoseTurn = static_cast<Play::player>(whoseTurn % 2 + 1);
    theWinner = myBoard->checkForWinner();
    if (theWinner == W::NOTFINISHED) {
        // round is not finished
        std::cout << myBoard->toString() << std::endl;
        turn();
    } else {
        // round is over
        std::cout << theWinner << std::endl;
        newRound(); // never terminates
    }
    
    
}
int Game::turnNum(){
    return numTerms;
}
int Game::roundNum(){
    return numRounds;
}

