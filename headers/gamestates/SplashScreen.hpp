#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Game.hpp"

class CSplashScreen{
	private:
		const unsigned short animation_constant = 4;

		sf::Text _splash_text;
		sf::Font _splash_font;
		sf::SoundBuffer *_s_buffer = new sf::SoundBuffer;
		sf::Sound *_s_sound = new sf::Sound;
		std::string _e_splash_string = "T  I  C  T  A  C  T  O  E",
					_j_font = "assets/fonts/japanese.ttf",
					_e_font = "assets/fonts/english.ttf",
					_audio = "assets/audio/start.wav";
		unsigned int _WIDTH,_HEIGHT;
		unsigned int _opacity=0;
		bool _reached_peak_brightness = false,
			_sound_played = false;
	
	public:
		CSplashScreen(){
			_s_buffer->loadFromFile(_audio);
			_s_sound->setBuffer(*_s_buffer);
			_splash_font.loadFromFile(_j_font);
		}
		bool render(sf::RenderWindow& window){
			if(!_sound_played){
				_s_sound->play();
				_sound_played = true;
			}
			_WIDTH = window.getSize().x;
			_HEIGHT = window.getSize().y;
			

			_splash_text.setString(_e_splash_string);
			_splash_text.setFont(_splash_font);
			_splash_text.setCharacterSize(100);
			_splash_text.setPosition(_WIDTH*0.2, _HEIGHT*0.3);

			window.draw(_splash_text);
			return _setTransparency();
		}
		void handleInput(sf::Event& event){std::cout << "SplashScreen";}
		
	private:
		bool _setTransparency(){
			_splash_text.setFillColor(sf::Color(255,255,255,_opacity));
			if (!_reached_peak_brightness){
				if(_opacity > 250)
					_reached_peak_brightness = true;
				else
					_opacity+=animation_constant;
			}
			else
				_opacity-=animation_constant;

			if(_reached_peak_brightness && _opacity <= 0){
				delete _s_sound;
				delete _s_buffer;
				_sound_played = false;
				return true;
			}
			return false;
		}
};