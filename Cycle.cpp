#include <iostream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include "ACharacter.hh"
#include "Cycle.hh"

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

	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		x = i % mapSizeX;
		y = i / mapSizeX;
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
	bool found = false;
	char input;

	while (true)
	{
		found = false;
		input = getchar();
		system("clear");
		if (input == ' ')
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
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if ((*it)->getEatable())
			(*it)->decrease();
	}
}

void	Cycle::cleanAll()
{
	// Check if a bonus is eaten, if so, detach player and (for special bonuses) monsters
	for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); it++) {
		if ((*it)->getLifePoints() <= 0)
		{
			Bonus* tmp = *it;
			(*it)->detach(_player);
			if ((*it)->isSpecial()) {
				for (std::list<Monster *>::iterator itMonster = _monsters.begin(); itMonster != _monsters.end(); itMonster++) {
					(*it)->detach(*itMonster);
				}
			}
			it = _bonus.erase(it);
			delete tmp;
		}
	}
	// Check if monsters are eaten, if so, detach map and players
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if ((*it)->getLifePoints() <= 0)
		{
			Monster* tmp = *it;
			(*it)->detach(_player);
			(*it)->detach(_map);
			it = _monsters.erase(it);
			delete tmp;
		}
	}
	// Check if the player is eaten, if so, detach map, monsters and bonuses
	if (_player->getLifePoints() <= 0) {
		_player->detach(_map);
		for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
			_player->detach(*it);
		}
		for (std::list<Bonus *>::iterator it = _bonus.begin(); it != _bonus.end(); it++) {
			_player->detach(*it);
		}
	}
}

void	Cycle::display() const {
	std::string	tmpMap(_map->getMap());
	// Add objects to the map
	for (std::list<Monster *>::const_iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if ((*it)->getEatable()) {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'W';
		} else {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'M';
		}
	}
	for (std::list<Bonus *>::const_iterator it = _bonus.begin(); it != _bonus.end(); it++) {
		if ((*it)->isSpecial()) {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = 'o';
		} else {
			tmpMap[(*it)->getPosx() + (*it)->getPosy() * _map->getWidth()] = '.';
		}
	}
	tmpMap[_player->getPosx() + _player->getPosy() * _map->getWidth()] = 'P';
	// Display Map
	for (int y = 0; y < _map->getHeight(); y++) {
		for (int x= 0; x < _map->getWidth(); x++) {
			std::cout << tmpMap[y * _map->getWidth() + x];
		}
		std::cout << std::endl;
	}
}

void	Cycle::gameLoop()
{
  while (_player->getLifePoints() >= 0)
    {
      getUserInput();
      _player->move();
	for (std::list<Monster *>::iterator it = _monsters.begin(); it != _monsters.end(); it++)
	  (*it)->move();
      display();


    }
}
