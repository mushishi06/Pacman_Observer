#include "Cycle.hh"

Cycle::Cycle()
{
	this->initialize();
}

void	Cycle::initialize() {
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

	// Attach everything correctly
	// Monster 	attach Map, Player
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		(*it)->attach(_map);
		(*it)->attach(_player);
	}
	// Bonus 	attach Player
	// S.Bonus 	attach Monster, Player
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); it++) {
		(*it)->attach(_player);
		if ((*it)->isSpecial()) {
			for (std::list<Monster *>::iterator itMonster = _monsters.begin(); itMonster != _monsters.end(); itMonster++) {
				(*it)->attach(*itMonster);
			}
		}
	}
	// Player 	attach Bonus, Map, Monster
	_player->attach(_map);
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		_player->attach(*it);
	}
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); it++) {
		_player->attach(*it);
	}
}

Cycle::~Cycle()
{
	delete _map;
	delete _player;
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		delete *it;
	}
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); it++) {
		delete *it;
	}
}


void	Cycle::checkEatable()
{
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if ((*it)->getEatable())
			(*it)->decrease();
	}
}

void	Cycle::display() const {
	std::string	tmpMap(map);
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
	}
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); it++) {
	}
}
