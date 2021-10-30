#pragma once
#include <SFML/Graphics.hpp>
#include "../Game.hpp"

class CMenu
{
public:
	CMenu(){}

//	TODO
//	FIND A WAY TO GET REFERENCE TO ENUM VARIABLE _GameState _CurrentState

	void handleInput(sf::Event& event/* _GameState& state */){std::cout << "Menu";}
	void render(sf::RenderWindow& window){
		std::cout << "Menu rendering..." << std::endl;
	}
};