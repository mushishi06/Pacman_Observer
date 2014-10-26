#ifndef PLAYER_HH_
# define PLAYER_HH_

#include "ACharacter.hh"

class Player : public ACharacter
{
public:
	Player(int posX, int posY, std::string const &image, std::string const &name = "Player", int points = 0);
	~Player();

	virtual void update(Subject *sub);
	
protected:
	Player();
};

std::ostream& operator<<(std::ostream& os, const Player& player);

#endif