#pragma once
#include "TictactoeOnline.hpp"	//Includes base tictactoe class as well
#include "gamestates/SplashScreen.hpp"
#include "gamestates/Menu.hpp"
#include "gamestates/Offline.hpp"
#include "gamestates/Online.hpp"
#include "gamestates/Winner.hpp"
#include "gamestates/Exit.hpp"

#include <SFML/Graphics.hpp>
#include <any>

class Game:public TicTacToeOnline{
	private:
		sf::RenderWindow _window;
		sf::Event _events;
		
		unsigned short _HEIGHT, _WIDTH, _FRAMERATE;

		bool _is_running;

		enum _GameState {SplashScreen, Menu, Offline, Online, Winner, Exit};

		std::vector<std::any> _GameMap;

		_GameState _currentState;

	protected:
				

	public:
		Game();
		void start();
		bool isGameRunning();

	private:
		void _renderState();
		void _handleInputs();
		void _createState();
		void _storeStates();
};