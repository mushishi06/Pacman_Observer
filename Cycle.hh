#ifndef CYCLE_HH_
# define CYCLE_HH_

#include <vector>
#include <termios.h>
#include "ChangeManager.hh"

class Cycle
{
public:
	Cycle();
	~Cycle();
	
	char getUserInput() const;

private:
	std::vector<char>	_authorizedMoves;
	struct termios		_t;
};

#endif