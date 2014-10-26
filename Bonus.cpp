#include "Bonus.hh"

Bonus::Bonus(int posX, int posY, std::string const &image, std::string const &name, bool special, int points)
: GameElement(name, points), _special(special)
{
	this->lifePoints = 1;
	this->posX = posX;
	this->posY = posY;
	this->image = image;
}

Bonus::~Bonus()
{
}

void Bonus::update(Subject *sub)
{
	std::cerr << this->name << ": update()" << std::endl;
	GameElement *elem = dynamic_cast<GameElement *>(sub);

	std::cerr << "sub is == " << elem->getName() << std::endl;
	if (elem->getPosx() == this->posX && elem->getPosy() == this->posY)
	{
		std::cerr << this->name << ": is getting eaten" << std::endl;
		--this->lifePoints;
		this->notify();
	}
}

bool	Bonus::isSpecial() const
{
	return (this->_special);
}
