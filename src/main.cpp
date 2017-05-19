// Copyright 2017 Zac Schulwolf

#include "game.h"
#include "net/src/log/logging.h"

LogLevel loglevel;

int main() {
	loglevel = logPROGRESS;
    tictac::Game* myGame = new tictac::Game();
    myGame->start();
    return 0;
}
