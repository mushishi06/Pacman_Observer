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

	void		changeDirection(Direction dir);
	void		move();
	Direction	getDirection() const;

protected:
	Direction	direction;

};

#endif