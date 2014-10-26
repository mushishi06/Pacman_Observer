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

void	ACharacter::move(int x, int y)
{
	std::cout << "Moving to x = " << x << " - y = " << y << std::endl;
	this->posX = x;
	this->posY = y;
}

ACharacter::Direction	ACharacter::getDirection() const
{
	return (this->direction);
}
