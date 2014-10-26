#include "Cycle.hh"

Cycle::Cycle()
{
	std::string map = "#############################............##............##.####.#####.##.#####.####.##o####.#####.##.#####.####o##.####.#####.##.#####.####.##..........................##.####.##.########.##.####.##.####.##.########.##.####.##......##....##....##......#######.##### ## #####.############.##### ## #####.########.....##          ##.....####.###.## ###++### ##.###.####.###.## #++++++# ##.###.####o....   #++++++#   ....o####.###.## #++++++# ##.###.####.###.## ######## ##.###.####.....##          ##.....########.## ######## ##.############.## ######## ##.#######............##............##.####.#####.##.#####.####.##.####.#####.##.#####.####.##o..##................##..o####.##.##.########.##.##.######.##.##.########.##.##.####......##....##....##......##.##########.##.##########.##.##########.##.##########.##..........................#############################";
	int			mapSizeX = 28;
	int			mapSizeY = 31;

	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		if (map[i] == '.') {
			// Create bonuses
			_gameElements.push_back(new Bonus(i % mapSizeX, (i - (i % mapSizeX)) / mapSizeY, "", "Bonus"));
		} else if (map[i] == 'o') {
			// Create special bonuses
			_gameElements.push_back(new Bonus(i % mapSizeX, (i - (i % mapSizeX)) / mapSizeY, "", "Special bonus"));
		} else if (map[i] == 'o') {
			// Create special bonuses
			_gameElements.push_back(new Bonus(i % mapSizeX, (i - (i % mapSizeX)) / mapSizeY, "", "Special bonus"));
		}
	}
	

	// Create monsters

	// Create player

	// Create map
	_map = new Map(map, mapSizeX, mapSizeY);
}

Cycle::~Cycle()
{
	delete _map;
}


void	Cycle::checkEatable()
{
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if ((*it)->getEatable())
			(*it)->decrease();
	}
}

