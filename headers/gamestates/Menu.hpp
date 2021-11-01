#pragma once

#include "../Game.hpp"
#include "../GameStates.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
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
		sf::Sprite _background_sprite, _face_sprite;

		bool _hover_played;

		float _WIDTH, _HEIGHT;
		float _t_posX, _t_posY;

		unsigned int _current_face = 0;

		enum _entities {_TITLE, _OFFLINE, _ONLINE, _EXIT};

		struct _FaceItem{
			float position_x=-200, position_y=-200;
			float rotation_angle=0;
			sf::Texture texture;
			unsigned int x_rate=rand()%10, y_rate = rand()%10, rotation_rate=rand()%4+1;
			bool has_been_seen = false;
		} _face[3];
		
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

			std::string picture_file = "assets/pictures/face_ .png";
			for(int i=0;i<3;i++){
				picture_file.replace(21,1,std::to_string(i));
				_face[i].texture.loadFromFile(picture_file);
			}
			
			_background_texture.loadFromFile("assets/pictures/background.jpg");

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
		void _updateFace(_FaceItem& current_face){
			current_face.rotation_angle+=current_face.rotation_rate;
			current_face.position_x+=current_face.x_rate;
			current_face.position_y+=current_face.y_rate;

			//Change face if previous face is out of window area and if it has previously been inside view
			if(((current_face.position_x > _WIDTH+current_face.texture.getSize().x or current_face.position_y > _HEIGHT+current_face.texture.getSize().y))){
				int sign = rand()%2;

				current_face.position_x = (rand()%(int)_WIDTH)-current_face.texture.getSize().x;
				current_face.position_y = sign*_HEIGHT+(pow(-1,sign+1))*current_face.texture.getSize().y;

				current_face.x_rate = rand()%5+1;
				current_face.y_rate = pow(-1,sign)*(rand()%4+1);

				current_face.rotation_rate = rand()%4+1;

				_current_face = (_current_face+1)%3;
			}
		}
		void _updateEntities(){
			_WIDTH = _window->getSize().x;
			_HEIGHT = _window->getSize().y;

			if(!(_s_sound_main->getStatus() == sf::Sound::Playing))
				_s_sound_main->play();

			_background_sprite.setTexture(_background_texture);

			_updateFace(_face[_current_face]);

			_face_sprite.setTexture(_face[_current_face].texture);
			_face_sprite.setPosition(_face[_current_face].position_x, _face[_current_face].position_y);
			_face_sprite.setRotation(_face[_current_face].rotation_angle);

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

			_updateEntities();

			_window->draw(_background_sprite);

			_window->draw(_face_sprite);

			for(int i=_TITLE; i <= _EXIT; i++){
				_rect_obj.setSize(_items[i].r_size);
				_rect_obj.setPosition(_items[i].r_position);
				_rect_obj.setSize(_items[i].r_size);
				_rect_obj.setOutlineColor(sf::Color(50,50,100));

				//Change color if rect object contains mouse pointer and play hover sound
				if (i != _TITLE){
					if(_rect_obj.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)))){
						if(_s_sound_other->getStatus() != sf::Sound::Playing && !_hover_played){
							_s_sound_other->play();
							_hover_played = true;
						}
						_items[i].b_color = sf::Color(200,200,200,50);
						_items[i].t_color = sf::Color::Cyan;
						_rect_obj.setOutlineThickness(10);
					}else{
						_hover_played = false;
						_items[i].b_color = sf::Color(200,200,200,10);
						_items[i].t_color = sf::Color(200,0,0);
						_rect_obj.setOutlineThickness(0);
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