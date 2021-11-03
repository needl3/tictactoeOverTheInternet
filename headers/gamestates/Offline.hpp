#pragma once
#include "../GameRenderer.hpp"
#include "../Tictactoe.hpp"

class COffline: public GameRenderer<TicTacToe>{
	public:
		COffline(sf::RenderWindow& window, sf::Event& event, TicTacToe& game):GameRenderer(window, event, game){}
};
