#include <stdexcept> 
#include "ACharacter.hh"

ACharacter::ACharacter(Direction dir)
: direction(dir)
{
}

ACharacter::~ACharacter()
{

}

void	ACharacter::changeDirection(ACharacter::Direction dir)
{
	static std::string const dirName[4] = {"up", "right", "down", "left"};

	std::cout << "Changing direction to " << dirName[dir] << std::endl;
	this->direction = dir;
}

void	ACharacter::move()
{
	int		previousPosX = this->posX;
	int		previousPosY = this->posY;
	switch (this->direction) {
		case ACharacter::UP:
			this->posY--;
			break;
		case ACharacter::RIGHT:
			this->posX++;
			break;
		case ACharacter::DOWN:
			this->posY++;
			break;
		case ACharacter::LEFT:
			this->posX--;
			break;
		default:
			break;
	}
	try {
		// Notify ChangeManager
		std::cout << "Current position is (" << previousPosX << ";" << previousPosY << "), moving to (" << this->posX << ";" << this->posY << ")" << std::endl;
		this->notify();
	} catch (std::exception e) {
		// Can't move to new position
		std::cout << "Can't move, stay in the same position" << std::endl;
		this->posX = previousPosX;
		this->posY = previousPosY;
	}
}

ACharacter::Direction	ACharacter::getDirection() const
{
	return (this->direction);
}
