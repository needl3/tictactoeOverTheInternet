#pragma once
#include <SFML/Network.hpp>
#include "Tictactoe.hpp"
#include <iostream>

class TicTacToeOnline:public TicTacToe{
	private:
		sf::IpAddress *_ADDRESS;
		sf::TcpSocket _SOCKET;
		sf::TcpListener _LISTENER;

		int _PORT=9999;
		char _buffer;
		std::size_t _received = 0;

	public:
		~TicTacToeOnline();
	
	private:
		void _sendMove(unsigned short);

		bool _establishConnection(bool host = false);

		unsigned short _waitForResponse();
		

		//Overloading functions
		void askTurn();
		unsigned short getMove();
};
