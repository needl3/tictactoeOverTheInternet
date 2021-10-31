#include "../headers/Game.hpp"

Game::Game(){
	_FRAMERATE = 40;
	_WIDTH = sf::VideoMode::getDesktopMode().width;
	_HEIGHT = sf::VideoMode::getDesktopMode().height;

	_window.create(sf::VideoMode(_WIDTH,_HEIGHT), "TicTacToe");
	_window.setFramerateLimit(_FRAMERATE);
	_storeStates();

	_currentState = Menu;
}

void Game::_storeStates(){
	CSplashScreen s_screen;
	CMenu menu;
	_GameMap.push_back(s_screen);
	_GameMap.push_back(menu);

}

bool Game::isGameRunning(){
	return _is_running;
}

void Game::start(){
	while(_window.isOpen()){
		_window.clear();
		_handleInputs();
		_renderState();
		_window.display();
	}
}
void Game::_renderState(){
	switch(_currentState){
		case SplashScreen:
			if(std::any_cast<CSplashScreen>(&_GameMap[_currentState])->render(_window))
				_currentState = GameState::Menu;	//Advance to menu after splashscreen animation ends
			break;
		case Menu:
			std::any_cast<CMenu>(&_GameMap[_currentState])->render(_window);
			break;
		case Offline:
			std::any_cast<COffline>(&_GameMap[_currentState])->render(_window);
			break;
		case Online:
			std::any_cast<COnline>(&_GameMap[_currentState])->render(_window);
			break;
		case Winner:
			std::any_cast<CWinner>(&_GameMap[_currentState])->render(_window);
			break;
		case Exit:
			std::any_cast<CExit>(&_GameMap[_currentState])->render(_window);
			break;
		default:
			std::cout << "No renderer..." << std::endl;
	}
}
void Game::_handleInputs(){
	_window.pollEvent(_events);
	switch(_events.type){
		case sf::Event::Closed:
			_window.close();
		case sf::Event::KeyPressed:
			if (_events.key.code == sf::Keyboard::Q)
				_window.close();
			break;
		case sf::Event::MouseButtonPressed:
			switch(_currentState){
				case Menu:
					_currentState = std::any_cast<CMenu>(&_GameMap[_currentState])->handleInput(_events);
					if(_currentState == Offline)
						ttt = new TicTacToe;
					else if(_currentState == Online)
						ttt =  new TicTacToeOnline;
					break;
				case Offline:
					std::any_cast<COffline>(&_GameMap[_currentState])->handleInput(_events);
					break;
				case Online:
					std::any_cast<COnline>(&_GameMap[_currentState])->handleInput(_events);
					break;
				case Winner:
					std::any_cast<CWinner>(&_GameMap[_currentState])->handleInput(_events);
					break;
				case Exit:
					std::any_cast<CExit>(&_GameMap[_currentState])->handleInput(_events);
					break;
				default:
					std::cout << "No handler";
			}
			break;
	}
}