#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include "Monster.hh"

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
	this->name = name;
	this->eatable = false;
	this->_time = 0;
}

void	Monster::update(Subject *sub)
{
	std::cout << this->name << " update" << std::endl;
	GameElement *elem = dynamic_cast<GameElement *>(sub);

	if (elem->getLifePoints() == 0)
		{
			this->eatable = true;
			this->_time = 5;
		}
	else if (elem->getPosx() == this->posX && elem->getPosy() == this->posY)
		this->notify();
}

void	Monster::move() {
	int previousPosX = this->posX;
	int previousPosY = this->posY;
	std::vector<ACharacter::Direction> validDirections;

	// Try to go forward
	try {
		this->updateNewPosition(this->direction);
		this->notify();
		validDirections.push_back(this->direction);
	} catch (std::exception e) {}
	// Try to go right from current direction
	try {
		this->posX = previousPosX;
		this->posY = previousPosY;
		this->updateNewPosition(static_cast<ACharacter::Direction>((this->direction + 1) % 4));
		this->notify();
		validDirections.push_back(static_cast<ACharacter::Direction>((this->direction + 1) % 4));
	} catch (std::exception e) {}
	// Try to go left from current direction
	try {
		this->posX = previousPosX;
		this->posY = previousPosY;
		this->updateNewPosition(static_cast<ACharacter::Direction>((this->direction + 3) % 4));
		this->notify();
		validDirections.push_back(static_cast<ACharacter::Direction>((this->direction + 3) % 4));
	} catch (std::exception e) {}

	// Randomize valid directions
	std::random_shuffle(validDirections.begin(), validDirections.end());
	// Choose random direction
	this->direction = validDirections.back();
	// Update position with current direction
	this->posX = previousPosX;
	this->posY = previousPosY;
	this->updateNewPosition(this->direction);
	// And finally, move !
	this->notify();
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
