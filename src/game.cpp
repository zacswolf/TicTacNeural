// Copyright 2017 Zac Schulwolf

#include "game.h"
#include <numeric>

namespace tictac {
Game::Game() {
    whoseTurn = player::PLAYER1;
    numTurns = 0;
    numRounds = 1;
    theWinner = winner::NOTFINISHED;
    started = player::PLAYER1;
    myBoard = new Board();
    
    csv.open ("TrainingData.csv", std::ofstream::app);
    if (!csv.is_open())
    {
        std::cout << "Error opening file";
        endGame();
    }
}
Game::~Game() {
	delete myBoard;
}

void Game::start() {
    csv << "\n4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0";
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
    csv << "\n4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0";
    doTurn();
}
void Game::doTurn() {
    numTurns++;
    std::string choice;
    std::cout << "Input for " << this->whoseTurn << ": ";
    std::cin >> choice;
    if (choice == "q"){ // END CONDITION
        endGame();
    } else {
        while ((!(myBoard->set(static_cast<position::position>(std::stoi(choice)), static_cast<tile::tile>(whoseTurn) ))) || std::stoi(choice) < 0 || std::stoi(choice) > 8) {
            std::cout << "Invalid Input! " << std::endl;
            std::cout << "Input for " << this->whoseTurn << ": ";
            std::cin >> choice;
        }
        whoseTurn = static_cast<player::player>(whoseTurn % 2 + 1);
        theWinner = myBoard->checkForWinner();
        
        
        // record to csv
        csv << ", " << choice;
        csv << ", " << whoseTurn % 2 + 1;
        csv << "\n";
        
        csv << theWinner;
        int ZeroPos[9];
        for (int i = 0; i < 9; i++){
            ZeroPos[i] = (myBoard->get(i) == tile::EMPTY);
            csv << ", " << ZeroPos[i];
        }
        int OnePos[9];
        for (int i = 0; i < 9; i++){
            OnePos[i] = (myBoard->get(i) == tile::PLAYER1);
            csv << ", " << OnePos[i];
        }
        int TwoPos[9];
        for (int i = 0; i < 9; i++){
            TwoPos[i] = (myBoard->get(i) == tile::PLAYER2);
            csv << ", " << TwoPos[i];
        }
        
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
}
size_t Game::turnNum() {
    return numTurns;
}
size_t Game::roundNum() {
    return numRounds;
}
void Game::endGame() {
    csv.close();
    delete myBoard;
}

// loads the network from filename into net
void SingleGame::loadNetwork(std::string filename, network::Network& net) {
	net = network::Network(filename);
}
// returns a vector of moves in order of preference
// for example, if 2, 7, 3 are the best moves in that order,
// the vector will start {2, 7, 3, ...}
// note that the moves will sometimes be invalid, so that's why a vector is used
std::vector<size_t> SingleGame::getMove(double_v vals, network::Network& net) {
	double_v results = net.feedforward(vals);
	std::vector<size_t> indices(results.size());
	std::iota(indices.begin(), indices.end(), static_cast<size_t>(0));
	std::sort(indices.begin(), indices.end(), [&results] (size_t a, size_t b) { return results[a] < results[b]; });
	return indices;
}
}
