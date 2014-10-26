#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>      // std::srand
#include "GameElement.hh"
#include "Bonus.hh"
#include "Map.hh"
#include "Player.hh"
#include "Monster.hh"
#include "Cycle.hh"

int main(int ac, char **av)
{
	std::srand(unsigned(std::time(0)));
	// Map settings

	std::string map1 = "#############################M...........##...........M##.####.#####.##.#####.####.##o####.#####.##.#####.####o##.####.#####.##.#####.####.##..........................##.####.##.########.##.####.##.####.##.########.##.####.##......##....##....##......#######.##### ## #####.############.##### ## #####.########.....##    P     ##.....####.###.## ######## ##.###.####.###.## #      # ##.###.####o....   #      #   ....o####.###.## #      # ##.###.####.###.## ######## ##.###.####.....##          ##.....########.## ######## ##.############.## ######## ##.#######............##............##.####.#####.##.#####.####.##.####.#####.##.#####.####.##o..##................##..o####.##.##.########.##.##.######.##.##.########.##.##.####......##....##....##......##.##########.##.##########.##.##########.##.##########.##M........................M#############################";
	int			map1SizeX = 28;
	int			map1SizeY = 31;

	std::string map2 = "#####################M     o           ## ###### ## ###### ##    #  .##.  #    #####   ######   #####P   #  .##.  #    ## ###### ## ###### ##           o     M#####################";
	int			map2SizeX = 20;
	int			map2SizeY = 9;

	std::string map = "";
	int			mapSizeX = 0;
	int			mapSizeY = 0;

	if (ac == 2 && std::string(av[1]) == "--map2") {
		map = map2;
		mapSizeX = map2SizeX;
		mapSizeY = map2SizeY;
	} else if ((ac == 2 && std::string(av[1]) == "--map1") || ac == 1) {
		map = map1;
		mapSizeX = map1SizeX;
		mapSizeY = map1SizeY;
	} else if (ac >= 2) {
		std::cout << "Invalid arguments, try '" << av[0] << "', '" << av[0] << " --map1' or '" << av[0] << " --map2'" << std::endl;
		return (-1);
	}

	Cycle	c;
	c.initialize(map, mapSizeX, mapSizeY);
	c.display();

	c.gameLoop();
	//std::cout << "type smth" << std::endl;
	//	char cmd = c.getUserInput();
	//	std::cout << "Commande is == " << cmd << std::endl;
	return (0);
}
