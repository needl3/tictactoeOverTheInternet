#pragma once
#include "../GameRenderer.hpp"
#include "../Tictactoe.hpp"
#include "EstablishConnection.hpp"
#include "Chooser.hpp"
#include "../GameStates.hpp"

class COnline: public GameRenderer<TicTacToeOnline>{

	private:
		sf::RenderWindow *_window;
		short _is_host = -1;	//-1-Not chosen		0-Host		1-Not Host
		EstablishConnection *_connect;
		enum {CONFIRM_HOST = 2};
		TicTacToeOnline *_game;

	public:
		COnline(sf::RenderWindow& window, sf::Event& event, TicTacToeOnline& game):GameRenderer(window, event, game){
			_connect = new EstablishConnection(window, event,game);
			_window = &window;
			_game = &game;
		}
		GameState handleInput(){
			if (_is_host == -1){
				_is_host = _turn_chooser->handleInput();
				if(_is_host>-1)
					_connect->setHost(!_is_host);
			}else if(!_is_connected){
				_is_connected = _connect->handleInput();
			}else if(_turn_chosen < 0){
				_turn_chosen = _turn_chooser->handleInput();
				if(_turn_chosen > -1){
					_game->askTurn((unsigned short)_turn_chosen);
				}
			}else{
				short move = _game->getMove(getGridPosition(sf::Mouse::getPosition(*_window)));
				if(GameRenderer<TicTacToeOnline>::handleInput(move)!=Offline)
					return Winner;
			}
			return Online;
		}
		void render(){
			GameRenderer<TicTacToeOnline>::render();
			if(_is_host == -1){
				_turn_chooser->setMode(CONFIRM_HOST);
				_turn_chooser->render();
			}else if(!_is_connected){
				_connect->render();
			}else if(_turn_chosen < 0){
				_turn_chooser->render();
			}
		}
};