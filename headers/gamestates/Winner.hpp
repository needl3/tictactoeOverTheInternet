#pragma once
#include <SFML/Graphics.hpp>
#include "../GameStates.hpp"
class CWinner
{
public:
	CWinner(sf::RenderWindow& window, sf::Event& event){
		
	}
	GameState handleInput(){
		return Winner;
	}
	void render(){
		std::cout << "rendering" << std::endl;
	}
};