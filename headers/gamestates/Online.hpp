#pragma once
#include "../GameRenderer.hpp"
#include "../Tictactoe.hpp"
class COnline: public GameRenderer<TicTacToeOnline>{
public:
	COnline(sf::RenderWindow& window, sf::Event& event, TicTacToeOnline& game):GameRenderer(window, event, game){
	}
	GameState handleInput(){
		return Online;
	}
	void render(){}
};