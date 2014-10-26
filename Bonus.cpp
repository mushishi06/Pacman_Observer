#include "Bonus.hh"

Bonus::Bonus(int posX, int posY, std::string const &image, int points, std::string const &name)
: GameElement(name, points)
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
	std::cout << this->name << " update" << std::endl;
	GameElement *elem = dynamic_cast<GameElement *>(sub);
	if (elem->getPosx() == this->posX && elem->getPosy() == this->posY)
	{
		--this->lifePoints;
		this->notify();
	}
}