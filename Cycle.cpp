#include "Cycle.hh"

Cycle::Cycle()
{
	std::string map = "#############################M...........##...........M##.####.#####.##.#####.####.##o####.#####.##.#####.####o##.####.#####.##.#####.####.##..........................##.####.##.########.##.####.##.####.##.########.##.####.##......##....##....##......#######.##### ## #####.############.##### ## #####.########.....##    P     ##.....####.###.## ###++### ##.###.####.###.## #++++++# ##.###.####o....   #++++++#   ....o####.###.## #++++++# ##.###.####.###.## ######## ##.###.####.....##          ##.....########.## ######## ##.############.## ######## ##.#######............##............##.####.#####.##.#####.####.##.####.#####.##.#####.####.##o..##................##..o####.##.##.########.##.##.######.##.##.########.##.##.####......##....##....##......##.##########.##.##########.##.##########.##.##########.##M........................M#############################";
	int			mapSizeX = 28;
	int			mapSizeY = 31;
	int			x = 0;
	int			y = 0;

	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		x = i % mapSizeX;
		y = (i - (i % mapSizeX)) / mapSizeY;
		if (map[i] == '.') {
			// Create bonuses
			_bonus.push_back(new Bonus(x, y, "", "Bonus"));
			map[i] = ' ';
		} else if (map[i] == 'o') {
			// Create special bonuses
			_bonus.push_back(new Bonus(x, y, "", "Special bonus", true, 20));
			map[i] = ' ';
		} else if (map[i] == 'M') {
			// Create monsters
			_monsters.push_back(new Monster(x, y, "", "Monster"));
			map[i] = ' ';
		} else if (map[i] == 'P') {
			// Create player
			_player = new Player(x, y, "", "Pacman");
			map[i] = ' ';
		}
	}

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

