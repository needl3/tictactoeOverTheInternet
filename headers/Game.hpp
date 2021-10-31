#pragma once
#include "TictactoeOnline.hpp"	//Includes base tictactow class as well
#include "gamestates/SplashScreen.hpp"
#include "gamestates/Menu.hpp"
#include "gamestates/Offline.hpp"
#include "gamestates/Online.hpp"
#include "gamestates/Winner.hpp"
#include "gamestates/Exit.hpp"
#include "GameStates.hpp"

#include <SFML/Graphics.hpp>
#include <any>
class Game{
	private:
		TicTacToe *ttt;
	protected:
		sf::RenderWindow _window;
		sf::Event _events;
		
		unsigned short _HEIGHT, _WIDTH, _FRAMERATE;

		bool _is_running;


		std::vector<std::any> _GameMap;

		GameState _currentState;

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