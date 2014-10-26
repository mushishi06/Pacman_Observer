#ifndef MONSTER_HH_
# define MONSTER_HH_

#include "ACharacter.hh"

class Monster : public ACharacter
{
public:
	Monster(int posX, int posY, std::string const &image, std::string const &name = "Monster", int points = 100);
	~Monster();
	
	virtual void update(Subject *sub);
	void 	decrease();
	virtual void	move();

protected:
	Monster();
	int		_time;
};

std::ostream& operator<<(std::ostream& os, const Monster& monster);

#endif