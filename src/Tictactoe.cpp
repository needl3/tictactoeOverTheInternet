#include "../headers/Tictactoe.hpp"
#include <iostream>
TicTacToe::TicTacToe(){
	//Generate move map and assign
	is_host = true;
	is_connected = -1;
	for(int i=0;i<_GRID_SIZE*_GRID_SIZE;i++){
			MOVE_MAP[i][0] = i/3;
			MOVE_MAP[i][1] = i%3;
	}
}

void TicTacToe::start(){
	bool is_running = true;
	int winner;
	askTurn();
	while(is_running){
		displayGrid();
		displayTurn();
		//Place Move
		while(!placeMove(MOVE_MAP[getMove()-1]));
		winner = checkWinner();
		if(winner != -1)
			is_running = false;
		toggleTurn();
	}
	toggleTurn();
	displayWinner(winner);
}
void TicTacToe::askTurn(){
	char opt;
	std::cout << std::endl << "Do you want to go first?(Y/N)";
	std::cin >> opt;
	if (opt == 'y')
		turn = YOU;
	else if(opt == 'n')
		turn = OPPONENT;
}
void TicTacToe::displayGrid(){
	std::cout << "-------------------------\n";
	for(int i=0;i<_GRID_SIZE;i++){
		for(int j=0;j<_GRID_SIZE;j++)
			std::cout << _grid[i][j] << "\t|";
		std::cout << "\n-------------------------";
		std::cout << std::endl;
	}
}
void TicTacToe::displayTurn(){
	std::cout << std::endl << "Current Turn: ";
	if(turn == YOU)
		std::cout << "YOU" << std::endl;
	else
		std::cout << "OPPONENT" << std::endl;
}
void TicTacToe::toggleTurn(){
	if(turn == YOU)
		turn = OPPONENT;
	else
		turn = YOU;
}
bool TicTacToe::placeMove(const unsigned short *position, bool check /*=false*/){
	if(_grid[position[0]][position[1]])
		return false;
	if(!check)
		_grid[position[0]][position[1]] = turn;
	return true;
}
unsigned short TicTacToe::getMove(){
	unsigned short move=-1;
	while(move < 1 or move >9){
		std::cout << std::endl << "Enter your Move Position=> ";
		std::cin >> move;
	}
	return move;
}
int TicTacToe::checkWinner(){
	//Row check and column check and diagonal check
	int countLR = 0;		//Left top to right bottom
	int countRL = 0;		//Right Bottom to left top
	int totalMoves = 0;
	for (int i=0; i<_GRID_SIZE; i++){
		//Row and column check block
		int countRow = 0;
		int countColumn = 0;
		for (int j=0;j<_GRID_SIZE;j++){
			if (_grid[i][j] != ' ')
				totalMoves++;
			if (_grid[i][j] == turn)
				countRow++;
			if (_grid[j][i] == turn)
				countColumn++;
		}
		if (countRow == _GRID_SIZE || countColumn == _GRID_SIZE)
			return turn;

		//Diagonal check block
		if (_grid[i][i] == turn)
			countLR++;
		if (_grid[_GRID_SIZE-i-1][i] == turn)
			countRL++;
	}
	if (countRL == _GRID_SIZE  || countLR == _GRID_SIZE)
		return turn;
	if (totalMoves == _GRID_SIZE*_GRID_SIZE){
		return -1;
	}
	return -2;
}
void TicTacToe::displayWinner(int winner){
	if (winner != -2){
		std::cout << "Winner is: ";
		if(turn == YOU)
			std::cout << "YOU" << std::endl;
		else
			std::cout << "OPPONENT" << std::endl;
	}
	else
		std::cout << "GAME DRAW" << std::endl;
}
void TicTacToe::clearGrid(){
	for (int i=0;i<_GRID_SIZE;i++){
		for (int j=0;j<_GRID_SIZE;j++){
			_grid[i][j] = 0;
		}
	}
}