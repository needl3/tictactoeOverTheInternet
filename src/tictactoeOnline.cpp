#include "../headers/tictactoeOnline.hpp"

TicTacToeOnline::TicTacToeOnline(){
	char will_host;
	while(will_host != 'y' && will_host != 'n'){
		std::cout << "Do you want to host the game?(Y/N)";
		std::cin >> will_host;
	}
	is_host = true ? (will_host == 'y') : false;
	verifyConnection(is_host);
}
TicTacToeOnline::~TicTacToeOnline(){
	//SEND Socket disconnect signal
	SOCKET.disconnect();
	LISTENER.close();
}
bool TicTacToeOnline::verifyConnection(bool host /*= false*/){
	std::string host_url;
	int host_port;
	if (!host){
		do{
			std::cout << "Enter remote host URL: ";
			std::cin >> host_url;
			std::cout << std::endl << "Enter remote host port: ";
			std::cin >> host_port;
		}while(SOCKET.connect(host_url, host_port) != sf::Socket::Done);
		ADDRESS = new sf::IpAddress(host_url);
		PORT = host_port;
	}else{
		std::cout << "Enter your public URL: ";
		std::cin >> host_url;
		std::cout << "Enter port for incoming connections: ";
		std::cin >> host_port;
		std::cout << "Waiting for incoming connections on "<< host_url << ":" << host_port << "..." << std::endl;
		LISTENER.listen(host_port);
		LISTENER.accept(SOCKET);
		PORT = host_port;
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
		sendMove(move);
	}else{
		move = waitForResponse();
	}
	return move;
}
void TicTacToeOnline::askTurn(){
	char opt;
	if (!is_host){
		turn = waitForResponse();
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
		sendMove((unsigned short)turn);
		toggleTurn();
	}
}

void TicTacToeOnline::sendMove(unsigned short move){
	buffer = (char)move;
	if(SOCKET.send(&buffer, sizeof(buffer)) != sf::Socket::Done){
		std::cout << "Cannot send data...Connection corrupted" << std::endl;
		exit(0);
	}
}
unsigned short TicTacToeOnline::waitForResponse(){
	std::cout << "Waiting for response" << std::endl;
	if(SOCKET.receive(&buffer, sizeof(buffer), received)!= sf::Socket::Done){
		std::cout << "Connection corrupted" << std::endl;
		exit(0);	
	}
	return (int)buffer;
}