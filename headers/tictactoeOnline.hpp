#ifndef TICTACTOE_ONLINE_H
#define TICTACTOE_ONLINE_H
#include <SFML/Network.hpp>
#include "tictactoe.hpp"
#include <iostream>

class TicTacToeOnline: public TicTacToe{
	private:
		sf::IpAddress *ADDRESS;
		int PORT=9999;
		sf::TcpSocket SOCKET;
		sf::TcpListener LISTENER;
		char buffer;
		std::size_t received = 0;

	public:
		TicTacToeOnline();
		~TicTacToeOnline();
		unsigned short waitForResponse();
		void sendMove(unsigned short);
	
	private:
		bool verifyConnection(bool host = false);
		bool estabilishConnection();
		unsigned short getMove();
		void askTurn();
};

#endif