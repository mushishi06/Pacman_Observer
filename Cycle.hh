#ifndef CYCLE_HH_
# define CYCLE_HH_

#include	"ChangeManager.hh"
#include	"Monster.hh"


class Cycle
{
public:
	Cycle();
	~Cycle();

	void checkEatable();

private:
	std::list<Monster> monster;

};

#endif
