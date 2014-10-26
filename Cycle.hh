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

	void	display() const;
	void	checkEatable();

private:
	Map *						_map;
	std::list<Bonus *>			_bonus;
	Player *					_player;
	std::list<Monster *>		_monsters;
	void						initialize();
};

#endif
