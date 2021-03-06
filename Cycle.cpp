#include <iostream>
#include <sstream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include "ACharacter.hh"
#include "Cycle.hh"

static std::string intToString(int i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

Cycle::Cycle()
{
	this->_authorizedMoves['t'] = ACharacter::UP;
	this->_authorizedMoves['h'] = ACharacter::RIGHT;
	this->_authorizedMoves['g'] = ACharacter::DOWN;
	this->_authorizedMoves['f'] = ACharacter::LEFT;

	tcgetattr(0, &this->_t); //get the current terminal I/O structure
    this->_t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(0, TCSANOW, &this->_t); //Apply the new settings
}

void	Cycle::initialize(std::string map, int mapSizeX, int mapSizeY) {
	int			x = 0;
	int			y = 0;
	int			bonusId = 0;
	int			specialBonusId = 0;
	int			monsterId = 0;

	for (int i = 0; i < mapSizeX * mapSizeY; ++i) {
		x = i % mapSizeX;
		y = i / mapSizeX;
		if (map[i] == '.') {
			// Create bonuses
			_bonus.push_back(new Bonus(x, y, "", "Bonus " + intToString(bonusId)));
			map[i] = ' ';
			++bonusId;
		} else if (map[i] == 'o') {
			// Create special bonuses
			_bonus.push_back(new Bonus(x, y, "", "Special bonus " + intToString(specialBonusId), true, 20));
			map[i] = ' ';
			++specialBonusId;
		} else if (map[i] == 'M') {
			// Create monsters
			_monsters.push_back(new Monster(x, y, "", "Monster " + intToString(monsterId)));
			map[i] = ' ';
			++monsterId;
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
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		(*it)->attach(_map);
		(*it)->attach(_player);
	}
	// Bonus 	attach Player
	// S.Bonus 	attach Monster, Player
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
		(*it)->attach(_player);
		if ((*it)->isSpecial()) {
			for (std::list<Monster *>::iterator itMonster = _monsters.begin(); itMonster != _monsters.end(); ++itMonster) {
				(*it)->attach(*itMonster);
			}
		}
	}
	// Player 	attach Bonus, Map, Monster
	_player->attach(_map);
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		_player->attach(*it);
	}
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
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
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		delete *it;
	}
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
		delete *it;
	}
}

char Cycle::getUserInput() const
{
	bool found = false;
	char input;

	while (true)
	{
		found = false;
		input = getchar();
		//		system("clear");
		if (input == ' ' || input == 'q')
			return (input);

		for (std::map<char, ACharacter::Direction>::const_iterator it = this->_authorizedMoves.begin(); it != this->_authorizedMoves.end(); ++it)
		{
			if (it->first == input)
				{
					this->_player->changeDirection(it->second);
					found = true;
					break;
				}
		}
		if (!found)
			std::cout << "wrong command " << input << std::endl;
	}
	return ('\0');
}

void	Cycle::checkEatable()
{
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		if ((*it)->getEatable())
			(*it)->decrease();
	}
}

void	Cycle::cleanAll()
{
	// Check if a bonus is eaten, if so, detach player and (for special bonuses) monsters
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
		if ((*it)->getLifePoints() <= 0)
		{
			Bonus* tmp = *it;
			(_player)->detach(*it);
			if ((*it)->isSpecial()) {
				for (std::list<Monster *>::iterator itMonster = _monsters.begin(); itMonster != _monsters.end(); ++itMonster) {
					(*itMonster)->detach(*it);
				}
			}
			(*it)->detach_all();
			it = _bonus.erase(it);
			delete tmp;
			if (it == _bonus.end())
			  break;
		}
	}
	// Check if monsters are eaten, if so, detach map and players
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		if ((*it)->getLifePoints() <= 0)
		{
			Monster* tmp = *it;
			(_player)->detach(*it);
			for (std::list<Bonus *>::iterator itBonus = _bonus.begin(); itBonus != _bonus.end(); ++itBonus) {
				if ((*itBonus)->isSpecial()) {
					(*itBonus)->detach(*it);
				}
			}

			(*it)->detach_all();
			it = _monsters.erase(it);
			delete tmp;
			if (it == _monsters.end())
			  break;
		}
	}
	// Check if the player is eaten, if so, detach map, monsters and bonuses
	if (_player->getLifePoints() <= 0) {
		_player->detach(_map);
		for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
			(*it)->detach(_player);
		}
		for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
			(*it)->detach(_player);
		}
		_player->detach_all();
	}
}

void	Cycle::display() const {
	std::string	tmpMap(_map->getMap());
	// Add objects to the map
	for (std::list<Bonus *>::const_iterator it = _bonus.begin(); it != _bonus.end(); ++it) {
		if ((*it)->isSpecial()) {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'o';
		} else {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = '.';
		}
	}
	for (std::list<Monster *>::const_iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
		if ((*it)->getEatable()) {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'W';
		} else {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'M';
		}
	}
	tmpMap[_player->getPosx() + _player->getPosy() * _map->getWidth()] = 'P';
	// Display Map
	for (int y = 0; y < _map->getHeight(); y++) {
		for (int x= 0; x < _map->getWidth(); x++) {
			if (tmpMap[y * _map->getWidth() + x] == 'M') {
				std::cout << "\033[1;31m" << tmpMap[y * _map->getWidth() + x] << "\033[0m";
			} else if (tmpMap[y * _map->getWidth() + x] == 'W') {
				std::cout << "\033[1;32m" << tmpMap[y * _map->getWidth() + x] << "\033[0m";
			}  else if (tmpMap[y * _map->getWidth() + x] == 'P') {
				std::cout << "\033[1;34m" << tmpMap[y * _map->getWidth() + x] << "\033[0m";
			} else {
				std::cout << tmpMap[y * _map->getWidth() + x];
			}
		}
		std::cout << std::endl;
	}
}

void	Cycle::gameLoop()
{
	while (_player->getLifePoints() > 0)
	{
		display();
		if (_bonus.empty())
		{
			std::cout << "YOU WIN! You have " <<_player->getNbPoints() << " points" << std::endl;
			return ;
		}
		if (getUserInput() == 'q')
		{
			std::cout << "GOOD BYE! You have " <<_player->getNbPoints() << " points" << std::endl;
			return ;
		}
		system("clear");
		_player->move();
		if (_player->getLifePoints() <= 0)
		{
			std::cout << "YOU'RE DEAD! You have " <<_player->getNbPoints() << " points" << std::endl;
			return ;
		}
		for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); ++it) {
			std::cerr << "Moving monster " << (*it)->getName() << std::endl;
			(*it)->move();
			(*it)->decrease();
		}
		cleanAll();
	}
	std::cout << "YOU'RE DEAD! You have " <<_player->getNbPoints() << " points" << std::endl;
}
