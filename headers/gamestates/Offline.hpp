#pragma once
#include <SFML/Graphics.hpp>
class COffline
{
public:
	void handleInput(sf::Event& event){std::cout << "Menu";}
	void render(sf::RenderWindow& window){
		std::cout << "Rendering..." << std::endl;
	}
};