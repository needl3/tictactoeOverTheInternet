#include "../headers/TictactoeOnline.hpp"

TicTacToeOnline::~TicTacToeOnline(){
	//SEND _Socket disconnect signal
	_SOCKET.disconnect();
	_LISTENER.close();
}
bool TicTacToeOnline::_establishConnection(bool host /*= false*/){
	char will_host;
	while(will_host != 'y' && will_host != 'n'){
		std::cout << "Do you want to host the game?(Y/N)";
		std::cin >> will_host;
	}

	is_host = (will_host == 'y');

	std::string host_url;
	int host_port;
	if (!is_host){
		do{
			std::cout << "Enter remote host URL: ";
			std::cin >> host_url;
			std::cout << std::endl << "Enter remote host port: ";
			std::cin >> host_port;
		}while(_SOCKET.connect(host_url, host_port) != sf::Socket::Done);
		_ADDRESS = new sf::IpAddress(host_url);
		_PORT = host_port;
	}else{
		std::cout << "Enter your public URL: ";
		std::cin >> host_url;
		std::cout << "Enter port for incoming connections: ";
		std::cin >> host_port;
		std::cout << "Waiting for incoming connections on "<< host_url << ":" << host_port << "..." << std::endl;
		_LISTENER.listen(host_port);
		_LISTENER.accept(_SOCKET);
		_PORT = host_port;
	}
	return true;
}
unsigned short TicTacToeOnline::getMove(){
	unsigned short move=0;
	if (turn == YOU){
		while(move < 1 or move >9){
			std::cout << std::endl << "Enter your Move Position=> ";
			std::cin >> move;
		}
		_sendMove(move);
	}else{
		move = _waitForResponse();
	}
	return move;
}
void TicTacToeOnline::askTurn(){
	char opt;
	if (!is_host){
		turn = _waitForResponse();
		std::cout << turn;
	}
	else{
		std::cout << std::endl << "Do you want to go first?(Y/N)";
		std::cin >> opt;
		if (opt == 'y')
			turn = YOU;
		else if(opt == 'n')
			turn = OPPONENT;
		toggleTurn();
		_sendMove((unsigned short)turn);
		toggleTurn();
	}
}

void TicTacToeOnline::_sendMove(unsigned short move){
	_buffer = (char)move;
	if(_SOCKET.send(&_buffer, sizeof(_buffer)) != sf::Socket::Done){
		std::cout << "Cannot send data...Connection corrupted" << std::endl;
		exit(0);
	}
}
unsigned short TicTacToeOnline::_waitForResponse(){
	std::cout << "Waiting for response" << std::endl;
	if(_SOCKET.receive(&_buffer, sizeof(_buffer), _received)!= sf::Socket::Done){
		std::cout << "Connection corrupted" << std::endl;
		exit(0);	
	}
	return (int)_buffer;
}