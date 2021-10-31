#include "../headers/Game.hpp"
#include <iostream>
#include <any>

class A{
public:
	virtual void give(){std::cout << "A";}
};
class B:public A{
public:
	void give(){std::cout << "B";}
};
int main()
{
	Game game;
	game.start();
	return 0;

}
