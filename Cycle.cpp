#include <iostream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include "Cycle.hh"

Cycle::Cycle()
{
	static char moves[4] = {'t', 'f', 'g', 'h'};
	int i = 0;

	while (i < 4)
	{
		this->_authorizedMoves.push_back(moves[i]);
		++i;
	}

	tcgetattr(0, &this->_t); //get the current terminal I/O structure
    this->_t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(0, TCSANOW, &this->_t); //Apply the new settings

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
	tcgetattr(0, &this->_t); //get the current terminal I/O structure
    this->_t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(0, TCSANOW, &this->_t); //Apply the new settings

    delete _map;
	delete _player;
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		delete *it;
	}
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); it++) {
		delete *it;
	}
}

char Cycle::getUserInput() const
{
	char input;

	input = getchar();

	for (std::vector<char>::const_iterator it = this->_authorizedMoves.begin(); it != this->_authorizedMoves.end(); ++it)
	{
		if (*it == input)
			return (input);
	}
	std::cout << "wrong command " << input << std::endl;
	return ('\0');
}

void	Cycle::checkEatable()
{
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if ((*it)->getEatable())
			(*it)->decrease();
	}
}

void	Cycle::display() const {

}
