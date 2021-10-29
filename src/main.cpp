#include <iostream>
#include "../headers/tictactoeOnline.hpp"
#include <SFML/Network.hpp>
int main()
{
	TicTacToeOnline game;
//	TicTacToe game;
	char exit='n';
	while(exit != 'y'){
		game.start();
		std::cout << std::endl << "Exit?(Y/N)" << std::endl;
		std::cin >> exit;
	}
	return 0;
}