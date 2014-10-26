#ifndef BONUS_HH_
# define BONUS_HH_

#include "GameElement.hh"

class Bonus : public GameElement
{
public:
	Bonus(int posX, int posY, std::string const &image, std::string const &name = "Bonus", int points = 1);
	~Bonus();
	
	virtual void update(Subject *sub);
protected:
	Bonus();

};

#endif