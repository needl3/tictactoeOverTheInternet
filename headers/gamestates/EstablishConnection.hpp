#pragma once

#include <SFML/Graphics.hpp>
#include "../GameStates.hpp"


class EstablishConnection{
	private:
		sf::RenderWindow *_window;
		sf::Event		 *_events;

		unsigned short _WIDTH;
		unsigned short _HEIGHT;

		sf::RectangleShape _rect;
		sf::Text _text;
		sf::Font _font;

		enum {BASE, URL, PORT, OK};

		struct {
			float posX, posY;
			float sizeX, sizeY;
			std::string label;
		} _items[4];

	private:
		void _updateEntities(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			_items[BASE].sizeX = _WIDTH;
			_items[BASE].sizeY = _HEIGHT/2.0f;
			_items[BASE].posX = 0;
			_items[BASE].posY = (_HEIGHT-_items[BASE].sizeY)/2.0f;

			_items[URL].sizeX = _WIDTH*0.8f;
			_items[URL].sizeY = _HEIGHT*0.2f;
			_items[URL].posX = _items[BASE].posX+(_items[BASE].sizeX-_items[URL].sizeX)/2.0f;
			_items[URL].posY = _items[BASE].posY+(_items[BASE].sizeY/2.0f-_items[URL].sizeY)/2.0f;

			_items[PORT].sizeX = _WIDTH*0.5f;
			_items[PORT].sizeY = _items[URL].sizeY;
			_items[PORT].posX = _items[URL].posX;
			_items[PORT].posY = _items[BASE].posY+_items[BASE].sizeX-(_items[BASE].sizeY/2.0f-_items[PORT].sizeY)/2.0f;
		}

	public:
		EstablishConnection(sf::RenderWindow& window, sf::Event& event){
			_window = &window;
			_events = &event;

			_font.loadFromFile("assets/fonts/japanese.ttf");

		}
		void handleInput(bool is_host){

		}
		void render(){
			_updateEntities();
			for(int i=BASE;i<=OK;i++){
				_rect.setSize(sf::Vector2f(_items[i].sizeX, _items[i].sizeY));
				_rect.setPosition(_items[i].posX, _items[i].posY);
				_window->draw(_rect);
			}
		}
};