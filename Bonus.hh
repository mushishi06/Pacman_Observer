#ifndef BONUS_HH_
# define BONUS_HH_

#include "GameElement.hh"

class Bonus : public GameElement
{
public:
	Bonus(int posX, int posY, std::string const &image, int points = 1, std::string const &name = "Bonus");
	~Bonus();
	
	virtual void update(Subject *sub);
protected:
	Bonus();

};

#endif