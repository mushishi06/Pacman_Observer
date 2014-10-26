#ifndef CYCLE_HH_
# define CYCLE_HH_

#include <vector>
#include <map>
#include <termios.h>
#include "ChangeManager.hh"
#include	"GameElement.hh"
#include "ACharacter.hh"
#include	"Map.hh"
#include	"Player.hh"
#include	"Monster.hh"
#include	"Bonus.hh"

class Cycle
{
public:
	Cycle();
	~Cycle();
	void	display() const;
	void	checkEatable();
	void	cleanAll();
	void	gameLoop();
	char	getUserInput() const;
	void	initialize(std::string map, int mapSizeX, int mapSizeY);

private:
	std::map<char, ACharacter::Direction>	_authorizedMoves;
	struct termios		_t;
	Map *						_map;
	std::list<Bonus *>			_bonus;
	Player *					_player;
	std::list<Monster *>		_monsters;
};

#endif
