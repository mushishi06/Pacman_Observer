#include <cstdlib>      // std::rand
#include <vector>       // std::vector
#include "Monster.hh"

/*
** To see all the elements of the class easly 
*/
std::ostream& operator<<(std::ostream& os, const Monster& monster)
{
	static std::string const dir[4] = {"up", "right", "down", "left"};

  	os << monster.getName() << " posX = " << monster.getPosx() << " - posY = " << monster.getPosy() << " - points = " << monster.getNbPoints() << " direction = " << dir[monster.getDirection()];
  	return os;
}

Monster::Monster(int posX, int posY, std::string const &image, std::string const &name, int points)
	: ACharacter(ACharacter::UP)
{
	this->posX = posX;
	this->posY = posY;
	this->image = image;
	this->nbPoints = points;
	this->lifePoints = 1;
	this->name = name;
	this->eatable = false;
	this->_time = 0;
}

void	Monster::update(Subject *sub)
{
	std::cerr << this->name << ": update()" << std::endl;
	GameElement *elem = dynamic_cast<GameElement *>(sub);

	if (elem->getLifePoints() == 0)
	{
		this->eatable = true;
		this->_time = 150;
	}
	else if (elem->getPosx() == this->posX && elem->getPosy() == this->posY)
	{
		if (this->eatable == true)
			--this->lifePoints;
		this->notify();
	}
}

void	Monster::move() {
	int previousPosX = this->posX;
	int previousPosY = this->posY;
	ACharacter::Direction previousDirection = this->direction;

	int randomDirection = std::rand() % 3;
	if (randomDirection == 0) {
		// Try to go forward
		try {
			this->updateNewPosition(this->direction);
			this->notify();
		} catch (std::exception e) {
			// Failed to move in that direction, try again
			this->posX = previousPosX;
			this->posY = previousPosY;
			this->move();
		}	
	} else if (randomDirection == 1) {
		// Try to go right from current direction
		try {
			this->direction = static_cast<ACharacter::Direction>((this->direction + 1) % 4);
			this->updateNewPosition(this->direction);
			this->notify();
		} catch (std::exception e) {
			// Failed to move in that direction, try again
			this->posX = previousPosX;
			this->posY = previousPosY;
			this->direction = previousDirection;
			this->move();
		}
	} else {
		// Try to go left from current direction
		try {
			this->direction = static_cast<ACharacter::Direction>((this->direction + 3) % 4);
			this->updateNewPosition(this->direction);
			this->notify();
		} catch (std::exception e) {
			// Failed to move in that direction, try again
			this->posX = previousPosX;
			this->posY = previousPosY;
			this->direction = previousDirection;
			this->move();
		}
	}
}

void	Monster::decrease()
{
	if (this->_time > 0)
	{
		this->_time -= 1;
		if (this->_time == 0)
			this->eatable = false;
	}
}

Monster::~Monster()
{

}
