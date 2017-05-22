// Copyright 2017 Zac Schulwolf

#include "game.h"
#include <numeric>

#define BLANK_BOARD "4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0"

namespace tictac {
Game::Game() {
    whoseTurn = player::PLAYER1;
    numTurns = 0;
    numRounds = 1;
    theWinner = winner::NOTFINISHED;
    started = player::PLAYER1;
    myBoard = new Board();
    isAI = false;
    ai = nullptr;
    lastMove = -1;
    
    csv.open ("TrainingData.csv", std::ofstream::app);
    if (!csv.is_open()) {
        std::cout << "Error opening file";
        endGame();
    }
}
Game::Game(std::string filename) {
    whoseTurn = player::PLAYER1;
    numTurns = 0;
    numRounds = 1;
    theWinner = winner::NOTFINISHED;
    started = player::PLAYER1;
    myBoard = new Board();
    isAI = true;
    ai = new network::Network(filename);
}
Game::~Game() {
	delete myBoard;
    delete ai;
}

void Game::start() {
    csv << "\n";
    csv << BLANK_BOARD;
	doTurn();
}

void Game::newRound() {
    numRounds++;
    myBoard->clear();
    /*
    whoseTurn = static_cast<player::player>(whoseTurn % 2 + 1);
    if (theWinner == player::PLAYER1 || theWinner == player::PLAYER2) {
        // player won
        started = static_cast<player::player>(theWinner);
    } else {
        // tie, switch first turn
        started = whoseTurn;
    }
    */
    whoseTurn = player::PLAYER1;
    csv << "\n";
    csv << BLANK_BOARD;
    doTurn();
}

std::vector<size_t> Game::getBoardState() {
    std::vector<size_t> result;
    for (int i = 0; i < 9; ++i) {
        result.push_back(this->myBoard->get(i) == tile::EMPTY);
    }
    for (int i = 0; i < 9; ++i) {
        result.push_back(this->myBoard->get(i) == tile::PLAYER1);
    }
    for (int i = 0; i < 9; ++i) {
        result.push_back(this->myBoard->get(i) == tile::PLAYER2);
    }
    return result;
}

bool Game::tryToPlay(int i) {
    bool done = (!(myBoard->set(static_cast<position::position>(i), static_cast<tile::tile>(whoseTurn) ))) || i < 0 || i > 8;
    if (done) {
        lastMove = i;
        return true;
    } else {
        return false;
    }
}

void Game::doTurn() {
    if (!isAI) doPlayerTurn();
    else {
        if (whoseTurn == player::PLAYER2) doAITurn();
        else doPlayerTurn();
    }

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

void Game::doAITurn() {
    double_v data;
    data.push_back(winner::NOTFINISHED);
    for (size_t i: getBoardState()) {
        data.push_back(static_cast<double>(i));
    }

    double_v results = ai->feedforward(data);
    std::vector<size_t> best(results.size());
    std::iota(best.begin(), best.end(), static_cast<size_t>(0));
    std::sort(best.begin(), best.end(), [&results] (size_t a, size_t b) { return results[a] < results[b]; });
    for (size_t i: best) {
        if (!tryToPlay(i)) break;
    }

    whoseTurn = static_cast<player::player>(whoseTurn % 2 + 1);
}

void Game::doPlayerTurn() {
    numTurns++;
    std::string choice;
    std::cout << "Input for " << this->whoseTurn << ": ";
    std::cin >> choice;
    if (choice == "q") { // END CONDITION
        endGame();
        exit(0);
    } else {
        while (tryToPlay(std::stoi(choice))) {
            std::cout << "Invalid Input! " << std::endl;
            std::cout << "Input for " << this->whoseTurn << ": ";
            std::cin >> choice;
        }
        whoseTurn = static_cast<player::player>(whoseTurn % 2 + 1);
        theWinner = myBoard->checkForWinner();
        
        // record to csv
        if (!isAI) {
            csv << ", " << choice;
            csv << ", " << whoseTurn % 2 + 1;
            csv << "\n";
            
            csv << theWinner;
            std::vector<size_t> boardState = getBoardState();
            for (size_t i: boardState) {
                csv << ", " << i;
            }
        }
    }
}
size_t Game::turnNum() {
    return numTurns;
}
size_t Game::roundNum() {
    return numRounds;
}
void Game::endGame() {
    csv.close();
}
}
