#pragma once
#include "../GameRenderer.hpp"
#include "../Tictactoe.hpp"
#include "EstablishConnection.hpp"
#include "Chooser.hpp"
#include "../GameStates.hpp"
#include "../resources.hpp"

/*
	To Solve:
		find a way to detect packet retrieval without mousepressed event
*/

class COnline: public GameRenderer<TicTacToeOnline>{

	private:
		sf::RenderWindow *_window;
		sf::Event *_events;
		short _is_host = -1;	//-1-Not chosen		0-Host		1-Not Host
		EstablishConnection *_connect;
		enum {CONFIRM_HOST = 2};
		TicTacToeOnline *_game;

		//Resources for Waiting display
		sf::RectangleShape _rect;
		sf::Font _font;
		sf::Text _text;
		unsigned short character_size;

	public:
		COnline(sf::RenderWindow& window, sf::Event& event, TicTacToeOnline& game):GameRenderer(window, event, game){
			_connect = new EstablishConnection(window, event,game);
			_window = &window;
			_game = &game;
			_events = &event;

			_rect.setPosition(0,_HEIGHT/4.0f);
			_rect.setSize(sf::Vector2f(_WIDTH, _HEIGHT/2.0f));
			_rect.setFillColor(sf::Color(10,10,10));

			_font.loadFromFile(FONT_J);
			character_size = _WIDTH/(_text.getString().getSize()+5);
			character_size = 40;
			_text.setString("Waiting for host to choose the turn...");
			_text.setPosition((_WIDTH-_text.getString().getSize()*character_size)/2.0f, _rect.getPosition().y+character_size);
			_text.setCharacterSize(character_size);
			_text.setFillColor(sf::Color(200,200,200));
		}
		GameState handleInput(){
			if (_is_host == -1){
				_is_host = _turn_chooser->handleInput();
				if(_is_host>-1)
					_connect->setHost(!_is_host);
			}else if(!_is_connected){
				_is_connected = _connect->handleInput();
			}else if(_turn_chosen < 0){
				if(!_is_host){
					//If you are host
					_turn_chosen = _turn_chooser->handleInput();
					_game->sendMove(_turn_chosen);
				}else{
					_turn_chosen = !_game->waitForResponse();
				}

				_game->turn = _turn_chosen ? _game->OPPONENT : _game->YOU;
				_current_state = GAME;
			}else if(_current_state == GAME){
				short move;
				if(_game->turn == _game->YOU){
					move = getGridPosition(sf::Mouse::getPosition(*_window));
					if (_game->placeMove(_game->MOVE_MAP[move], true)){
						_game->sendMove(move);
					}
				}
				else{
					move = _game->waitForResponse();
				}

				_game->placeMove(_game->MOVE_MAP[move]);
				_winner = _game->checkWinner();
				if(_winner < 0)	_game->toggleTurn();
				else{
					_window->waitEvent(*_events);
					if(_events->type == sf::Event::MouseButtonReleased)
						_current_state = WINNER;
				}
			}else{
				if(GameRenderer<TicTacToeOnline>::handleInput() == Menu){
					_is_connected = false;
					_game->resetConnection();
					return Menu;
				}
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
				if(!_is_host){
					//If you are host
					_turn_chooser->render();
				}else{
					_renderWaiting();
				}
			}
		}
		void _renderWaiting(){
			_window->draw(this->_rect);
			_text.setFont(_font);
			_window->draw(this->_text);
		}
};