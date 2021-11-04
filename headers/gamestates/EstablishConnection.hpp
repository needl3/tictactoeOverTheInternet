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

		enum {BASE, URL, PORT, OK, URL_CONTAINER, PORT_CONTAINER};

		struct {
			float posX, posY;
			float sizeX, sizeY;
			std::string label;
			sf::Color color;
		} _items[6];

		bool _is_host;

	private:
		void _updateEntities(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			_items[BASE].sizeX = _WIDTH;
			_items[BASE].sizeY = _HEIGHT/2.0f;
			_items[BASE].posX = 0;
			_items[BASE].posY = (_HEIGHT-_items[BASE].sizeY)/2.0f;
			_items[BASE].color = sf::Color(100,200,100);

			_items[URL].sizeX = _items[BASE].sizeX*0.45f;
			_items[URL].sizeY = _items[BASE].sizeY*0.2f;
			_items[URL].posX = _items[BASE].posX+(_items[BASE].sizeX-_items[URL].sizeX)/9.0f;
			_items[URL].posY = _items[BASE].posY+(_items[BASE].sizeY/2.0f-_items[URL].sizeY)/2.0f;
			_items[URL].color = sf::Color(100,200,200,200);

			_items[PORT].sizeX = _items[URL].sizeX*0.5f;
			_items[PORT].sizeY = _items[URL].sizeY;
			_items[PORT].posX = _items[URL].posX;
			_items[PORT].posY = _items[URL].posY+_items[URL].sizeY+(_items[BASE].sizeY/2.0f-_items[PORT].sizeY)/2.0f;
			_items[PORT].color = _items[URL].color;

			_items[OK].sizeX = _items[PORT].sizeX*0.5f;
			_items[OK].sizeY = _items[PORT].sizeY;
			_items[OK].posX = _items[BASE].sizeX-_items[OK].sizeX*1.5;
			_items[OK].posY = _items[PORT].posY+_items[PORT].sizeY+_items[OK].sizeY*0.4;
			_items[OK].color = sf::Color(10,10,10,50);
			_items[OK].label = "OK";

			_items[URL_CONTAINER].sizeX = (_items[BASE].sizeX-_items[URL].sizeX)*0.7;
			_items[URL_CONTAINER].sizeY = _items[URL].sizeY*0.8;
			_items[URL_CONTAINER].posX = _items[URL].sizeX+_items[URL].posX+(_items[BASE].sizeX-_items[URL].posX-_items[URL].sizeX-_items[URL_CONTAINER].sizeX)/2.0f;
			_items[URL_CONTAINER].posY = _items[URL].posY+(_items[URL].sizeY-_items[URL_CONTAINER].sizeY)/2.0f;
			_items[URL_CONTAINER].color = sf::Color(10,10,10,50);
			_items[URL_CONTAINER].label = "|";

			_items[PORT_CONTAINER].sizeX = (_items[BASE].sizeX-_items[URL].sizeX)*0.3;
			_items[PORT_CONTAINER].sizeY = _items[PORT].sizeY*0.8;
			_items[PORT_CONTAINER].posX = _items[URL_CONTAINER].posX;
			_items[PORT_CONTAINER].posY = _items[PORT].posY+(_items[PORT].sizeY-_items[PORT_CONTAINER].sizeY)/2.0f;
			_items[PORT_CONTAINER].color = sf::Color(10,10,10,50);
			_items[PORT_CONTAINER].label = "|";
			
		}

	public:
		EstablishConnection(sf::RenderWindow& window, sf::Event& event){
			_window = &window;
			_events = &event;

			_font.loadFromFile("assets/fonts/japanese.ttf");

		}
		bool handleInput(){

			return false;
		}
		void render(){
			_updateEntities();
			for(int i=BASE;i<=PORT_CONTAINER;i++){
				sf::Color highlighting_color(50,50,50);

				_rect.setSize(sf::Vector2f(_items[i].sizeX, _items[i].sizeY));
				_rect.setPosition(_items[i].posX, _items[i].posY);
				if(_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)))
					and i == OK)
					_rect.setFillColor(_items[i].color+highlighting_color);
				else
					_rect.setFillColor(_items[i].color);
				_window->draw(_rect);


				unsigned short character_size = _items[i].sizeY/2.0f;
				float posX = _items[i].posX + character_size;
				float posY = _items[i].posY+(_items[i].sizeY-character_size)/2.0f;
				_text.setFont(_font);
				_text.setString(_items[i].label);
				_text.setPosition(posX, posY);
				_text.setCharacterSize(character_size);
				_text.setFillColor(sf::Color(200,0,0));
				_window->draw(_text);
			}
		}
		void setHost(bool is_host){
			_is_host = is_host;
			if(_is_host){
				_items[URL].label = "Enter your public/relay address";
				_items[PORT].label = "Enter listening port";
			}
			else{
				_items[URL].label = "Enter public/relay url of the host";
				_items[PORT].label = "Enter port";
			}
		}
};