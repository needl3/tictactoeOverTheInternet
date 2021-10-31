#pragma once

#include "../Game.hpp"
#include "../GameStates.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <any>

class CMenu{
	private:
		sf::RenderWindow *_window;
		sf::Event *_event;

		sf::Font _txt_font;
		
		sf::SoundBuffer *_s_buffer_main = new sf::SoundBuffer;
		sf::SoundBuffer *_s_buffer_option_hover = new sf::SoundBuffer;
		
		sf::Sound *_s_sound_main = new sf::Sound;
		sf::Sound *_s_sound_other = new sf::Sound;
		
		sf::Texture _background_texture;
		sf::Sprite _background_sprite;

		bool _hover_played;

		float _WIDTH=1080.0f, _HEIGHT=800.0f, _hover_offset=0.0f;
		float _t_posX, _t_posY;

		enum _entities {_TITLE, _OFFLINE, _ONLINE, _EXIT};
		
		struct _MenuItem{
			std::string label;
			sf::Vector2f r_size;
			sf::Vector2f r_position;
			sf::Color b_color, t_color;
		} _items[4];

		sf::Text _text_obj;
		sf::RectangleShape _rect_obj, temp_rect;

	public:
		CMenu(sf::RenderWindow& window, sf::Event& event){
			_window = &window;
			_event = &event;

			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

//------------------------------------------------------------------
			// TODO FIX SPRITE WHITE LOADING ISSUE
//------------------------------------------------------------------

			_background_texture.loadFromFile("assets/pictures/background.jpg");
			_background_sprite.setTexture(_background_texture);

			_s_buffer_main->loadFromFile("assets/audio/theme.wav");
			_s_sound_main->setBuffer(*_s_buffer_main);
			_s_sound_main->setLoop(true);

			_s_buffer_option_hover->loadFromFile("assets/audio/hover.wav");
			_s_sound_other->setBuffer(*_s_buffer_option_hover);

			_txt_font.loadFromFile("assets/fonts/japanese.ttf");

			_items[_TITLE].r_size = sf::Vector2f(_WIDTH*0.8, _HEIGHT*0.2);
			_items[_TITLE].r_position = sf::Vector2f(_WIDTH*0.2, 0);
			_items[_TITLE].b_color = sf::Color(200,200,200,0);
			_items[_TITLE].t_color = sf::Color(255,255,255,150);
			_items[_TITLE].label = "TICTACTOE";

			_items[_OFFLINE].r_size = sf::Vector2f(_WIDTH*0.3, _HEIGHT*0.2);
			_items[_OFFLINE].r_position = sf::Vector2f(_WIDTH*0.1, _HEIGHT*0.4);
			_items[_OFFLINE].label = "OFFLINE";

			_items[_ONLINE].r_size = sf::Vector2f(_WIDTH*0.3, _HEIGHT*0.2);
			_items[_ONLINE].r_position = sf::Vector2f(_WIDTH*0.6, _HEIGHT*0.4);
			_items[_ONLINE].label = "ONLINE";

			_items[_EXIT].r_size = sf::Vector2f(_WIDTH*0.1, _HEIGHT*0.1);
			_items[_EXIT].r_position = sf::Vector2f(_WIDTH*0.8, _HEIGHT*0.8);
			_items[_EXIT].label = "EXIT";
		}
		void _updateEntities(){
			if(!(_s_sound_main->getStatus() == sf::Sound::Playing))
				_s_sound_main->play();
		}
		GameState handleInput(){
			if(_event->type==sf::Event::MouseButtonPressed){
				for(int i=_OFFLINE; i <= _EXIT; i++){
					_rect_obj.setPosition(_items[i].r_position);
					_rect_obj.setSize(_items[i].r_size);
					if(_rect_obj.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)))){
						_s_buffer_option_hover->loadFromFile("assets/audio/select.wav");
						_s_sound_other->setBuffer(*_s_buffer_option_hover);
						_s_sound_other->play();
						return static_cast<GameState>(i+1);
					}
				}
			}
			return Menu;
		}
		void render(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			_updateEntities();

//			_window->draw(_background_sprite);

			for(int i=_TITLE; i <= _EXIT; i++){
				_rect_obj.setSize(_items[i].r_size);
				_rect_obj.setPosition(_items[i].r_position);
				_rect_obj.setSize(_items[i].r_size);

				//Change color if rect object contains mouse pointer and play hover sound
				if (i != _TITLE){
					if(_rect_obj.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)))){
						if(_s_sound_other->getStatus() != sf::Sound::Playing && !_hover_played){
							_s_sound_other->play();
							_hover_played = true;
						}
						_items[i].b_color = sf::Color(200,200,200,50);
						_items[i].t_color = sf::Color::Cyan;
					}else{
						_hover_played = false;
						_items[i].b_color = sf::Color(200,200,200,10);
						_items[i].t_color = sf::Color(200,0,0);
					}
				}
				_rect_obj.setFillColor(_items[i].b_color);
				_window->draw(_rect_obj);

				_text_obj.setFont(_txt_font);
				_text_obj.setString(_items[i].label);
				_text_obj.setFillColor(_items[i].t_color);
				_text_obj.setCharacterSize(_rect_obj.getSize().x/(_text_obj.getString().getSize()));

				_t_posX = _rect_obj.getGlobalBounds().left+(_rect_obj.getSize().x-_text_obj.getCharacterSize()*(_text_obj.getString().getSize()-1));
				_t_posY = _rect_obj.getGlobalBounds().top+(_rect_obj.getSize().y-_text_obj.getCharacterSize())/2.0;

				_text_obj.setPosition(sf::Vector2f(_t_posX, _t_posY));

				_window->draw(_text_obj);
			}
		}
};