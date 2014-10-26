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
	void	display() const;
	void	checkEatable();
	void	cleanAll();
	char	getUserInput() const;

private:
	std::vector<char>	_authorizedMoves;
	struct termios		_t;
	Map *						_map;
	std::list<Bonus *>			_bonus;
	Player *					_player;
	std::list<Monster *>		_monsters;
	void						initialize();
};

#endif
