#ifndef CYCLE_HH_
# define CYCLE_HH_

#include <vector>
#include <termios.h>
#include "ChangeManager.hh"
#include	"GameElement.hh"
#include	"Map.hh"
#include	"Player.hh"
#include	"Monster.hh"
#include	"Bonus.hh"

class Cycle
{
public:
	Cycle();
	~Cycle();
	
	char getUserInput() const;
	void checkEatable();

private:
	std::vector<char>	_authorizedMoves;
	struct termios		_t;
	Map *						_map;
	std::list<Bonus *>			_bonus;
	Player *					_player;
	std::list<Monster *>		_monsters;
	void						initialize();
	void						display() const;
};

#endif
