#pragma once
#include <SFML/Graphics.hpp>
#include "../Tictactoe.hpp"
#include "../GameStates.hpp"

class COffline: public TicTacToe{
	private:
		sf::RenderWindow *_window;
		sf::Event *_events;
		sf::RectangleShape _rect;
		sf::CircleShape _circle;

		enum _itemBox {GRID, YOU, OPPONENT, CONNECTION};

		struct {
			sf::RectangleShape rect_shape;
			unsigned short posX, posY, sizeX, sizeY;
		} _item[4];

		unsigned int _WIDTH, _HEIGHT;

	public:
		COffline(sf::RenderWindow& window, sf::Event& event){
			_window = &window;
			_events = &event;

			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;
			
			//For test
			_grid[1][2] = 'X';
			_grid[1][1] = 'O';
			_grid[2][1] = 'X';
			_grid[0][0] = 'O';
		}

		GameState handleInput(){
			std::cout << "Handling..." << std::endl;
			return Offline;
		}

		void render(){
			_updateDimentions();
			//Render grid lines -> grid
			//Render cross -> position
			//Render O -> position
			//Render Status Box --- OPPONENT
			//					|
			//					--- YOU

			_renderBackground();
			_renderGrid();
			_renderStatus();
			_renderConnection();
		}
	private:
		void _renderGrid(){
			for(int i=0;i<3;i++){
				for (int j=0;j<3;j++){
					if (i>0 && j>0)
						_renderLine(i,j);

					_renderMove(i,j, _grid[i][j]);
				}
			}
		}
		void _updateDimentions(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			_item[GRID].sizeX = 0.55*_WIDTH;
			_item[GRID].sizeY = 0.8*_HEIGHT;
			_item[GRID].posX = (_WIDTH-_item[GRID].sizeX)/2;
			_item[GRID].posY = (_HEIGHT-_item[GRID].sizeY)/2;

			_item[OPPONENT].sizeX = 0.2*_WIDTH;
			_item[OPPONENT].sizeY = 0.1*_HEIGHT;
			_item[OPPONENT].posX = (_WIDTH-2*_item[OPPONENT].sizeX-_item[GRID].sizeX)/2;
			_item[OPPONENT].posY = (_HEIGHT-2*_item[OPPONENT].sizeY-_item[GRID].sizeY)/2;

			_item[YOU].sizeX = 0.2*_WIDTH;
			_item[YOU].sizeY = 0.1*_HEIGHT;
			_item[YOU].posX = (_WIDTH-_item[YOU].sizeX)/2;
			_item[YOU].posY = (_HEIGHT-_item[YOU].sizeY)/2;

			_item[CONNECTION].sizeX = 0.1*_WIDTH;
			_item[CONNECTION].sizeY = 0.01*_HEIGHT;
			_item[CONNECTION].posX = (_WIDTH-_item[CONNECTION].sizeX)/2;
			_item[CONNECTION].posY = (_HEIGHT-_item[CONNECTION].sizeY);
		}
		void _renderBackground(){}
		void _renderStatus(){}
		void _renderConnection(){}
		void _renderMove(unsigned int i, unsigned int j, char symbol){
			if(symbol == 'X'){
				float hypotenuse=sqrt(pow(0.2*_item[GRID].sizeX,2)+pow(0.2*_item[GRID].sizeY,2));
				_rect.setPosition(_item[GRID].posX+j*0.37*_item[GRID].sizeX, _item[GRID].posY+i*0.4*_item[GRID].sizeY);
				_rect.setSize(sf::Vector2f(0.3*0.01*_item[GRID].sizeX, hypotenuse));
				_rect.setRotation(-55);
				_window->draw(_rect);

				_rect.setPosition(_item[GRID].posX+j*0.32*_item[GRID].sizeX+_item[GRID].sizeX*0.3, _item[GRID].posY+i*0.4*_item[GRID].sizeY);
				_rect.setRotation(55);
				_window->draw(_rect);
				_rect.setRotation(0);
			}else if(symbol == 'O'){
				_circle.setRadius(_item[GRID].sizeX*0.3/4);
				_circle.setFillColor(sf::Color::Black);
				_circle.setOutlineThickness(6);

				_circle.setPosition(_item[GRID].posX+(j*0.35+0.07)*_item[GRID].sizeX, _item[GRID].posY+(i*0.35+0.05)*_item[GRID].sizeY);
				_window->draw(_circle);
			}
		}
		void _renderLine(unsigned int i, unsigned int j){
			_rect.setPosition(_item[GRID].posX+i*_item[GRID].sizeX/3,_item[GRID].posY);
			_rect.setSize(sf::Vector2f(_item[GRID].sizeX*0.01,_item[GRID].sizeY));
			_rect.setFillColor(sf::Color::White);
			_window->draw(_rect);

			_rect.setPosition(_item[GRID].posX,_item[GRID].posY+j*_item[GRID].sizeY/3);
			_rect.setSize(sf::Vector2f(_item[GRID].sizeX,_item[GRID].sizeY*0.01));
			_rect.setFillColor(sf::Color::White);
			_window->draw(_rect);
		}
};