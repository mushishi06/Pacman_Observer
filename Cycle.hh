#ifndef CYCLE_HH_
# define CYCLE_HH_

#include	"ChangeManager.hh"
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

	void checkEatable();

private:
	Map *						_map;
	std::list<GameElement *>	_gameElements;
	std::list<Monster *>		_monsters;
};

#endif
