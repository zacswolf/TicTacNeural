#include "board.h"

Board::Board(){
	data.fill(EMPTY);
}

Board::set(int location, tile player){
	data[location] = player;
}

Board::get(int location){
	return data[location];
}
Board::isEmpty(int location){
	return board[location] == EMPTY;
}
Board::clear(){
	data.fill(EMPTY);
}
Board::readAll(){
	return data;
}

Board::toString(){
	return data;
}

Board::checkForWinner(){
	if (((data[4] == data[0] == data[8]) || (data[4] == data[2] == data[6]) || (data[4] == data[3] == data[5]) || 
		(data[4] == data[1] == data[7])) && (data[4] != EMPTY)) {
		// center tile
		// diag, diag, hor, vert
		return data[4];
    } else if (((data[0] == data[1] == data[2]) || (data[0] == data[3] == data[6])) && (data[0] != EMPTY)) {
		// top-left tile
		// hor, vert
		return data[0];
	} else if (((data[8] == data[7] == data[6]) || (data[8] == data[5] == data[2])) && (data[8] != EMPTY)) {
		// bottom-right tile
		// hor, vert
		return data[8];
	} else if (!((data[0] == EMPTY) || (data[1] == EMPTY) || (data[2] == EMPTY) || (data[3]] == EMPTY) || 
		(data[4] == EMPTY) || (data[5] == EMPTY) || (data[6] == EMPTY) || (data[7] == EMPTY) || (data[8] == EMPTY))) {
		// TIE
		return TIE;
	} else {
		// No winner
		return NOTFINISHED;
	}
}