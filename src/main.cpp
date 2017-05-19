// Copyright 2017 Zac Schulwolf

#include <iostream>
#include "game.h"
#include "net/src/log/logging.h"

LogLevel loglevel;

// TODO
// Make SingleGame() class (can be in the game.cpp file)

int main() {
    loglevel = logPROGRESS;
	int result = -1;
	while (result != 1 && result != 2) {
		std::cout << "Enter 1 for VS AI, 2 for VS yourself (training mode): ";
		std::cin >> result;
	}
	if (result == 2) {
    	tictac::Game* myGame = new tictac::Game();
    	myGame->start();
	} else if (result == 1) {
		// create instance of SingleGame()
		// I can provide method `int getMove(Board b)`
		// that calls from the neural network
	}
}
