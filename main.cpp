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
	// Map settings
	std::string map = "#############################M...........##...........M##.####.#####.##.#####.####.##o####.#####.##.#####.####o##.####.#####.##.#####.####.##..........................##.####.##.########.##.####.##.####.##.########.##.####.##......##....##....##......#######.##### ## #####.############.##### ## #####.########.....##    P     ##.....####.###.## ###++### ##.###.####.###.## #++++++# ##.###.####o....   #++++++#   ....o####.###.## #++++++# ##.###.####.###.## ######## ##.###.####.....##          ##.....########.## ######## ##.############.## ######## ##.#######............##............##.####.#####.##.#####.####.##.####.#####.##.#####.####.##o..##................##..o####.##.##.########.##.##.######.##.##.########.##.##.####......##....##....##......##.##########.##.##########.##.##########.##.##########.##M........................M#############################";
	int			mapSizeX = 28;
	int			mapSizeY = 31;
	

	Cycle	c;
	c.initialize(map, mapSizeX, mapSizeY);
	c.display();

	std::cout << "type smth" << std::endl;
	char cmd = c.getUserInput();
	std::cout << "Commande is == " << cmd << std::endl;
	return (0);
}