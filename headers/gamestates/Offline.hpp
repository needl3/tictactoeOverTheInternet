#pragma once
#include <SFML/Graphics.hpp>
#include "../Tictactoe.hpp"
#include "../GameStates.hpp"
#include "Chooser.hpp"

class COffline{
	private:
		sf::RenderWindow *_window;
		sf::Event *_events;
		TicTacToe *_game;
		Chooser *_turn_chooser;
		
		sf::Texture _background_texture;
		sf::Sprite _background_sprite;

		sf::RectangleShape _rect;
		sf::CircleShape _circle;

		sf::Text _text;
		sf::Font _txt_font;

		short _winner = -1;

		enum _itemBox {gOPPONENT, gYOU, GRID, CONNECTION};

		struct {
			sf::RectangleShape rect_shape;
			float posX, posY;
			float sizeX, sizeY;
			std::string stat1, stat2, label;
		} _item[4];

		struct{
			float hypotenuse;
			float x_offset;
			float y_offset;
			float grid_sizeX;
			float grid_sizeY;
			float line_sizeX;
			float line_sizeY;
		} _tileProperties;

		unsigned int _WIDTH, _HEIGHT;

		short _turn_chosen = -1;

	public:
		COffline(sf::RenderWindow& window, sf::Event& event, TicTacToe& game){
			_window = &window;
			_events = &event;
			_game = &game;

			_turn_chooser = new Chooser(_window,_events);

			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;
		
			_background_texture.loadFromFile("assets/pictures/background_play.jpg");
			_txt_font.loadFromFile("assets/fonts/japanese.ttf");

			//Defining constants
			_item[CONNECTION].stat1 = "CONNECTED";
			_item[CONNECTION].stat2 = "NOT CONNECTED";

			_item[gOPPONENT].stat1 = "CONSPIRING";
			_item[gOPPONENT].stat2 = "WAITING";
			_item[gOPPONENT].label = "OPPONENT";
		
			_item[gYOU].stat1 = "CONSPIRING";
			_item[gYOU].stat2 = "WAITING";
			_item[gYOU].label = "YOU";
		}

		GameState handleInput(){
			if(_turn_chosen > -1){
				short position = _getGridPosition(sf::Mouse::getPosition(*_window));
				if(position>-1){
					if(_game->placeMove(_game->MOVE_MAP[position])){
						_winner = _game->checkWinner();
						if(_winner > 0)
							return Winner;
						_game->toggleTurn();
					}
				}
			}else{
				// 1 indicates accepted to play first
				_turn_chosen = _turn_chooser->handleInput();
				if(_turn_chosen > -1)
					_game->turn = _turn_chosen ? _game->YOU : _game->OPPONENT;
			}
			return Offline;
		}

		void render(){
			_updateDimensions();
			_renderBackground();
			_renderGrid();
			_renderStatus();
			_renderConnection(false);
			if(_turn_chosen<0){
				_turn_chooser->render();
			}
		}
	private:
		short _getGridPosition(sf::Vector2i position){
			int x1,y1,x2,y2,count=0;
			for (int i=0;i<3;i++){
				for (int j=0;j<3;j++){
					x1 = _item[GRID].posX+j*(_tileProperties.grid_sizeX+_tileProperties.line_sizeX),
					y1 = _item[GRID].posY+i*(_tileProperties.grid_sizeY+_tileProperties.line_sizeY);
					x2 = x1+_tileProperties.grid_sizeX;
					y2 = y1+_tileProperties.grid_sizeY;

					if(position.x > x1 and position.x < x2 and position.y > y1 and position.y < y2)
						return count;
					count++;
				}
			}
			return -1;
		}
		void _renderGrid(){
			for(int i=0;i<3;i++){
				for (int j=0;j<3;j++){
					if (i>0 && j>0)
						_renderLine(i,j);
					_renderMove(i,j, _game->_grid[i][j]);
				}
			}
		}
		void _updateDimensions(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			_item[GRID].sizeX = 0.55f*_WIDTH;
			_item[GRID].sizeY = 0.8f*_HEIGHT;
			_item[GRID].posX = (_WIDTH-_item[GRID].sizeX)/2.0f;
			_item[GRID].posY = (_HEIGHT-_item[GRID].sizeY)/2.0f;

			_item[CONNECTION].sizeY = 0.04f*_HEIGHT;
			_item[CONNECTION].sizeX = _item[CONNECTION].sizeY*_item[CONNECTION].stat2.size();
			_item[CONNECTION].posX = (_WIDTH-_item[CONNECTION].sizeX)/2.0f;
			_item[CONNECTION].posY = (_HEIGHT-_item[CONNECTION].sizeY);

			_item[gOPPONENT].sizeX = (_WIDTH-_item[GRID].sizeX)/3.0f;
			_item[gOPPONENT].sizeY = _item[GRID].sizeY/5.0f;
			_item[gOPPONENT].posX = (_WIDTH-2*_item[gOPPONENT].sizeX-_item[GRID].sizeX)/4.0f;
			_item[gOPPONENT].posY = _item[GRID].posY+_item[GRID].sizeY/2.7f;

			_item[gYOU].sizeX = _item[gOPPONENT].sizeX;
			_item[gYOU].sizeY = _item[gOPPONENT].sizeY;
			_item[gYOU].posX = _WIDTH - _item[gOPPONENT].posX - _item[gOPPONENT].sizeX;
			_item[gYOU].posY = _item[gOPPONENT].posY;

			_tileProperties.hypotenuse=sqrt(pow(0.2f*_item[GRID].sizeX,2)+pow(0.2f*_item[GRID].sizeY,2));
			_tileProperties.x_offset = _item[GRID].sizeX*0.05f;
			_tileProperties.y_offset = _item[GRID].sizeY*0.05f;
			_tileProperties.grid_sizeX = _item[GRID].sizeX/3.0f;
			_tileProperties.grid_sizeY = _item[GRID].sizeY/3.0f;
			_tileProperties.line_sizeX = 0.01f*_item[GRID].sizeX;
			_tileProperties.line_sizeY = 0.01f*_item[GRID].sizeY;
		}
		void _renderBackground(){
			_background_sprite.setTexture(_background_texture);
			_window->draw(_background_sprite);
		}
		void _renderStatus(){
			unsigned short character_size = _item[gOPPONENT].sizeX/(_item[gOPPONENT].label.size()+5);
			//Background Base Rectangles and labels
			for(int i=gOPPONENT;i<=gYOU;i++){
				bool green=false;
				
				green = ((_game->turn == _game->OPPONENT and i==gOPPONENT) or (_game->turn == _game->YOU and i==gYOU));
				
				_rect.setPosition(_item[i].posX, _item[i].posY);
				_rect.setSize(sf::Vector2f(_item[i].sizeX, _item[i].sizeY));
				_rect.setFillColor(sf::Color(20*(!green),255*green,255*green,100));
				_window->draw(_rect);
	
				float txtX = _item[i].posX+(_item[i].sizeX-_item[i].label.size()*character_size)/2.0f;
				float txtY = _item[i].posY+character_size/2.0f;
				_text.setPosition(txtX,txtY);
				_text.setString(_item[i].label);
				_window->draw(_text);

				std::string stat = green ? _item[i].stat1 : _item[i].stat2;
				txtX = _item[i].posX+(_item[i].sizeX-stat.size()*character_size)/2.0f;
				txtY += character_size*3;
				_text.setPosition(txtX,txtY);
				_text.setString(stat);
				_window->draw(_text);
			}
		}
		void _renderConnection(bool connected = false){
			_rect.setPosition(_item[CONNECTION].posX, _item[CONNECTION].posY);
			_rect.setSize(sf::Vector2f(_item[CONNECTION].sizeX, _item[CONNECTION].sizeY));
			_rect.setFillColor(sf::Color(0,200,200,100));
			_window->draw(_rect);

			float character_size = _item[CONNECTION].sizeY;
			float textPositionX = _item[CONNECTION].posX+3*character_size;
			float textPositionY = _item[CONNECTION].posY-character_size/10.0f;
			if(connected){
				_text.setFillColor(sf::Color(0,200,100));
				_text.setString(_item[CONNECTION].stat1);
			}
			else{
				_text.setFillColor(sf::Color(200,50,50));
				_text.setString(_item[CONNECTION].stat2);
			}
			_text.setFont(_txt_font);
			_text.setCharacterSize(character_size);
			_text.setPosition(textPositionX,textPositionY);
			_window->draw(_text);
		}
		void _renderMove(unsigned int i, unsigned int j, char symbol){
			if(symbol == 'X'){
				_rect.setPosition(_item[GRID].posX+j*(_tileProperties.grid_sizeX+_tileProperties.line_sizeX)+_tileProperties.x_offset,
									_item[GRID].posY+i*(_tileProperties.grid_sizeY+_tileProperties.line_sizeY)+_tileProperties.y_offset);
				_rect.setSize(sf::Vector2f(0.3f*0.01f*_item[GRID].sizeX, _tileProperties.hypotenuse));
				_rect.setRotation(-55);
				_rect.setFillColor(sf::Color::White);
				_window->draw(_rect);


				_rect.setPosition(_item[GRID].posX+j*(_tileProperties.grid_sizeX+_tileProperties.line_sizeX)+_tileProperties.x_offset+0.2*_item[GRID].sizeX,
									_item[GRID].posY+i*(_tileProperties.grid_sizeY+_tileProperties.line_sizeY)+_tileProperties.y_offset);
				_rect.setRotation(55);
				_window->draw(_rect);
				_rect.setRotation(0);
			}else if(symbol == 'O'){
				_circle.setRadius(_item[GRID].sizeX*0.3/4);
				_circle.setFillColor(sf::Color(0,0,0,1));
				_circle.setOutlineThickness(6);

				_circle.setPosition(_item[GRID].posX+(j*0.35+0.07)*_item[GRID].sizeX, _item[GRID].posY+(i*0.35+0.05)*_item[GRID].sizeY);
				_window->draw(_circle);
			}
		}
		void _renderLine(unsigned int i, unsigned int j){
			//Vertical
			_rect.setPosition(_item[GRID].posX+i*_item[GRID].sizeX/3.0f,_item[GRID].posY);
			_rect.setSize(sf::Vector2f(_item[GRID].sizeX*0.01f,_item[GRID].sizeY));
			_rect.setFillColor(sf::Color::White);
			_window->draw(_rect);

			//Horizontal
			_rect.setPosition(_item[GRID].posX,_item[GRID].posY+j*_item[GRID].sizeY/3.0f);
			_rect.setSize(sf::Vector2f(_item[GRID].sizeX,_item[GRID].sizeY*0.01f));
			_rect.setFillColor(sf::Color::White);
			_window->draw(_rect);
		}
};