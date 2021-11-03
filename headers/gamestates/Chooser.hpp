#pragma once
#include <SFML/Graphics.hpp>
class Chooser{
	private:
		sf::RenderWindow *_window;
		sf::Event *_events;

		unsigned short _WIDTH, _HEIGHT;
		
		unsigned short mouseX;
		unsigned short mouseY;

		sf::RectangleShape _rect;
		sf::Text _text;

		enum {BASE,QUESTION,YE,NYE};

		struct{
			float posX,posY,sizeX,sizeY;
			std::string label;
			sf::Color color;
		} _item[4];

	public:
		Chooser(sf::RenderWindow* window, sf::Event* event){
			_window = window;
			_events = event;
		}
		void render(){
			_updateEntities();
			_renderEntities();
		}
		void _updateEntities(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			mouseX = sf::Mouse::getPosition(*_window).x;
			mouseY = sf::Mouse::getPosition(*_window).y;

			_item[BASE].sizeX = _WIDTH;
			_item[BASE].sizeY = _HEIGHT/2.0f;
			_item[BASE].posX = 0;
			_item[BASE].posY = (_HEIGHT-_item[BASE].sizeY)/2.0f;

			//I know i should implement them mathematically, but its late and i have to finish this shit off
			_item[QUESTION].sizeX = _item[BASE].sizeX*0.8f;
			_item[QUESTION].sizeY = _item[BASE].sizeY*0.2f;
			_item[QUESTION].posX = _item[BASE].posX+(_item[BASE].sizeX-_item[QUESTION].sizeX)/2.0f;
			_item[QUESTION].posY = _item[BASE].posY+(_item[BASE].sizeY-_item[QUESTION].sizeY)/4.0f;
			_item[QUESTION].label = "Do you want to go first?";

			_item[YE].sizeX = _item[BASE].sizeX*0.5f*0.3f;
			_item[YE].sizeY = _item[BASE].sizeY*0.2;
			_item[YE].posX = _item[QUESTION].posX+(_item[QUESTION].sizeX/2.0f-_item[YE].sizeX)/2.0f;
			_item[YE].posY = _item[QUESTION].posY+_item[QUESTION].sizeY*1.5;
			_item[YE].label = "YE";

			_item[NYE].sizeX = _item[YE].sizeX;
			_item[NYE].sizeY = _item[YE].sizeY;
			_item[NYE].posX = _item[QUESTION].posX+_item[QUESTION].sizeX/2.0f+(_item[QUESTION].sizeX/2.0f-_item[NYE].sizeX)/2.0f;
			_item[NYE].posY = _item[YE].posY;
			_item[NYE].label = "NYE";
		}
		void _renderEntities(){
			for(int i=BASE;i<=NYE;i++){
				if ((_item[i].posX < mouseX and _item[i].posX+_item[i].sizeX > mouseX) and
						(_item[i].posY < mouseY and _item[i].posY+_item[i].sizeY > mouseY) and i>=YE){
					_rect.setFillColor(sf::Color(10,255,255,150));
				}else{
					_rect.setFillColor(sf::Color(100,100,100,150));
				}

				_rect.setPosition(_item[i].posX, _item[i].posY);
				_rect.setSize(sf::Vector2f(_item[i].sizeX, _item[i].sizeY));
				_window->draw(_rect);

				float character_size = _item[i].sizeX/(_item[i].label.size()+2);
				float txtX = _item[i].posX+(_item[i].sizeX-_item[i].label.size()*character_size)/2.0f;
				float txtY = _item[i].posY+character_size/2.0f;

				_text.setString(_item[i].label);
				_text.setPosition(txtX,txtY);
				_text.setCharacterSize(character_size);
				_text.setFillColor(sf::Color::White);
				_window->draw(_text);

			}
		}

		short handleInput(){
			if(_events->type == sf::Event::MouseButtonPressed){
				_window->waitEvent(*_events);
				if(_events->type == sf::Event::MouseButtonReleased){
					for(int i=YE;i<=NYE;i++){
						if((_item[i].posX < mouseX and _item[i].posX+_item[i].sizeX > mouseX) and
						(_item[i].posY < mouseY and _item[i].posY+_item[i].sizeY > mouseY)){
							return i;
						}
					}
				}
			}
			return -1;
		}
};