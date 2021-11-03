#pragma once
#include <SFML/Graphics.hpp>
#include "Offline.hpp"
#include "../GameStates.hpp"
class COnline{
public:
	COnline(sf::RenderWindow& window, sf::Event& event, TicTacToeOnline& game){
		
	}
	GameState handleInput(){std::cout << "Menu";}
	void render(){}
};