#pragma once
#include <SFML/Graphics.hpp>
#include "GameStates.hpp"
#include "gamestates/Chooser.hpp"
#include <SFML/Audio.hpp>
#include <cmath>

template <typename T>
class GameRenderer{
	private:
		sf::RenderWindow *_window;
		sf::Event *_events;
		T *_game;
		

		sf::Texture _background_texture;
		sf::Sprite _background_sprite;

		sf::RectangleShape _rect;
		sf::CircleShape _circle;

		sf::Text _text;
		sf::Font _txt_font;


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


	protected:

		unsigned int _WIDTH, _HEIGHT;
		short _winner = -1;
		short _turn_chosen = -1;
		bool _is_connected = false;

		Chooser *_turn_chooser;

		short getGridPosition(sf::Vector2i);

		enum _States {TURN_CHOOSER, PLAY_AGAIN, WINNER, GAME};

		_States _current_state;

		sf::SoundBuffer _buf_win, _buf_lose, _buf_move;
		sf::Sound _sound;

	public:
		GameRenderer(sf::RenderWindow&, sf::Event&, T& game);
		void render();
		GameState handleInput();

	private:
		void prepareData(sf::RenderWindow&, sf::Event&);
		void _renderWinner();
		void _renderGrid();
		void _updateDimensions();
		void _renderBackground();
		void _renderStatus();
		void _renderConnection();
		void _renderMove(unsigned int, unsigned int, char);
		void _renderLine(unsigned int, unsigned int);

};