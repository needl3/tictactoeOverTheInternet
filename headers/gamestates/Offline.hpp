#pragma once
#include <SFML/Graphics.hpp>
#include "../Tictactoe.hpp"
#include "../GameStates.hpp"

class COffline: public TicTacToe{
	private:
		sf::RenderWindow *_window;
		sf::Event *_events;
		
		sf::Texture _background_texture;
		sf::Sprite _background_sprite;

		sf::RectangleShape _rect;
		sf::CircleShape _circle;

		sf::Text _text;
		sf::Font _txt_font;

		enum _itemBox {OPPONENT, YOU, GRID, CONNECTION};

		struct {
			sf::RectangleShape rect_shape;
			float posX, posY;
			float sizeX, sizeY;
			std::string stat1, stat2;
		} _item[4];

		unsigned int _WIDTH, _HEIGHT;

	public:
		COffline(sf::RenderWindow& window, sf::Event& event){
			_window = &window;
			_events = &event;

			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;
		
			_background_texture.loadFromFile("assets/pictures/background_play.jpg");
			_txt_font.loadFromFile("assets/fonts/japanese.ttf");

			//For test
			_grid[0][0] = 'O';
			_grid[0][1] = 'X';
			_grid[0][2] = 'X';
			_grid[1][0] = 'X';
			_grid[1][1] = 'O';
			_grid[1][2] = 'X';
			_grid[2][0] = 'X';
			_grid[2][1] = 'X';
			_grid[2][2] = 'O';
		}

		GameState handleInput(){
			std::cout << "Handling..." << std::endl;
			return Offline;
		}

		void render(){
			_updateDimensions();
			_renderBackground();
			_renderGrid();
			_renderStatus();
			_renderConnection(false);
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
		void _updateDimensions(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			_item[GRID].sizeX = 0.55f*_WIDTH;
			_item[GRID].sizeY = 0.8f*_HEIGHT;
			_item[GRID].posX = (_WIDTH-_item[GRID].sizeX)/2.0f;
			_item[GRID].posY = (_HEIGHT-_item[GRID].sizeY)/2.0f;


			_item[CONNECTION].stat1 = "CONNECTED";
			_item[CONNECTION].stat2 = "NOT CONNECTED";
			_item[CONNECTION].sizeY = 0.04f*_HEIGHT;
			_item[CONNECTION].sizeX = _item[CONNECTION].sizeY*_item[CONNECTION].stat2.size();
			_item[CONNECTION].posX = (_WIDTH-_item[CONNECTION].sizeX)/2.0f;
			_item[CONNECTION].posY = (_HEIGHT-_item[CONNECTION].sizeY);

			_item[OPPONENT].sizeX = (_WIDTH-_item[GRID].sizeX)/3.0f;
			_item[OPPONENT].sizeY = _item[GRID].sizeY/4.0f;
			_item[OPPONENT].posX = (_WIDTH-2*_item[OPPONENT].sizeX-_item[GRID].sizeX)/4.0f;
			_item[OPPONENT].posY = _item[GRID].posY+_item[GRID].sizeY/2.7f;
			_item[OPPONENT].stat1 = "CONSPIRING";
			_item[OPPONENT].stat2 = "WAITING";

			_item[YOU].sizeX = _item[OPPONENT].sizeX;
			_item[YOU].sizeY = _item[OPPONENT].sizeY;
			_item[YOU].posX = _WIDTH - _item[OPPONENT].posX - _item[OPPONENT].sizeX;
			_item[YOU].posY = _item[OPPONENT].posY;
			_item[YOU].stat1 = "CONSPIRING";
			_item[YOU].stat2 = "WAITING";
		}
		void _renderBackground(){
			_background_sprite.setTexture(_background_texture);
			_window->draw(_background_sprite);
		}
		void _renderStatus(){

			//Background Base Rectangles
			for(int i=OPPONENT;i<=YOU;i++){
				_rect.setPosition(_item[i].posX, _item[i].posY);
				_rect.setSize(sf::Vector2f(_item[i].sizeX, _item[i].sizeY));
				_rect.setFillColor(sf::Color(30,30,30,200));
				_window->draw(_rect);
			}

			_text.setPosition()
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
				float hypotenuse=sqrt(pow(0.2f*_item[GRID].sizeX,2)+pow(0.2f*_item[GRID].sizeY,2));
				float x_offset = _item[GRID].sizeX*0.05f;
				float y_offset = _item[GRID].sizeY*0.05f;
				float grid_sizeX = _item[GRID].sizeX/3.0f;
				float grid_sizeY = _item[GRID].sizeY/3.0f;
				float line_sizeX = 0.01f*_item[GRID].sizeX;
				float line_sizeY = 0.01f*_item[GRID].sizeY;

				_rect.setPosition(_item[GRID].posX+j*(grid_sizeX+line_sizeX)+x_offset,
									_item[GRID].posY+i*(grid_sizeY+line_sizeY)+y_offset);
				_rect.setSize(sf::Vector2f(0.3f*0.01f*_item[GRID].sizeX, hypotenuse));
				_rect.setRotation(-55);
				_rect.setFillColor(sf::Color::White);
				_window->draw(_rect);


				_rect.setPosition(_item[GRID].posX+j*(grid_sizeX+line_sizeX)+x_offset+0.2*_item[GRID].sizeX,
									_item[GRID].posY+i*(grid_sizeY+line_sizeY)+y_offset);
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
			_rect.setPosition(_item[GRID].posX+i*_item[GRID].sizeX/3.0f,_item[GRID].posY);
			_rect.setSize(sf::Vector2f(_item[GRID].sizeX*0.01f,_item[GRID].sizeY));
			_rect.setFillColor(sf::Color::White);
			_window->draw(_rect);

			_rect.setPosition(_item[GRID].posX,_item[GRID].posY+j*_item[GRID].sizeY/3.0f);
			_rect.setSize(sf::Vector2f(_item[GRID].sizeX,_item[GRID].sizeY*0.01f));
			_rect.setFillColor(sf::Color::White);
			_window->draw(_rect);
		}
};