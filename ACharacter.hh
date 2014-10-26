#ifndef ACHARACTER_HH_
# define ACHARACTER_HH_

#include "GameElement.hh"

class ACharacter: public GameElement
{
public:
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	ACharacter(Direction dir = LEFT);
	virtual ~ACharacter();

	virtual void update(Subject *sub) = 0;

protected:
	Direction	direction;

};

#endif