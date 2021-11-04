#pragma once
#include <SFML/Graphics.hpp>
#include "GameStates.hpp"
#include "gamestates/Chooser.hpp"
#include "gamestates/Winner.hpp"
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

		short _winner = -1;

		enum _itemBox {gOPPONENT, gYOU, GRID, CONNECTION};

		enum _States {TURN_CHOOSER, PLAY_AGAIN, WINNER, GAME};

		_States _current_state;

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

	protected:
		short _turn_chosen = -1;
		bool _is_connected = false;
		Chooser *_turn_chooser;

	public:
		GameRenderer(sf::RenderWindow&, sf::Event&, T& game);
		void render();
		GameState handleInput();

	private:
		void prepareData(sf::RenderWindow&, sf::Event&);
		short _getGridPosition(sf::Vector2i);
		void _renderWinner();
		void _renderGrid();
		void _updateDimensions();
		void _renderBackground();
		void _renderStatus();
		void _renderConnection();
		void _renderMove(unsigned int, unsigned int, char);
		void _renderLine(unsigned int, unsigned int);

};