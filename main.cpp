#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>      // std::srand
#include "GameElement.hh"
#include "Bonus.hh"
#include "Map.hh"
#include "Player.hh"
#include "Monster.hh"
#include "Cycle.hh"

int main()
{
	std::srand(unsigned(std::time(0)));
	Cycle	game;

	Cycle c;

	std::cout << "type smth" << std::endl;
	char cmd = c.getUserInput();
	std::cout << "Commande is == " << cmd << std::endl;
	return (0);
}