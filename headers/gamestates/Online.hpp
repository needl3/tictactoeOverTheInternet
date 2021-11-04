#pragma once
#include "../GameRenderer.hpp"
#include "../Tictactoe.hpp"
#include "EstablishConnection.hpp"
#include "Chooser.hpp"
#include "../GameStates.hpp"

class COnline: public GameRenderer<TicTacToeOnline>{

	private:
		short _is_host = -1;	//-1-Not chosen		0-Host		1-Not Host
		EstablishConnection *_connect;
		enum {CONFIRM_HOST = 2};

	public:
		COnline(sf::RenderWindow& window, sf::Event& event, TicTacToeOnline& game):GameRenderer(window, event, game){
			_connect = new EstablishConnection(window, event);
		}
		GameState handleInput(){
			if (_is_host == -1){
				_is_host = _turn_chooser->handleInput();
				if(_is_host>-1)
					_connect->setHost(_is_host);
			}else if(!_is_connected){
				_is_connected = _connect->handleInput();
			}else if(GameRenderer<TicTacToeOnline>::handleInput() == Menu){
				return Menu;
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
			}
		}
};