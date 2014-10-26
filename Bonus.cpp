#include "Bonus.hh"

Bonus::Bonus(int points)
: GameElement("Bonus", points)
{
	this->lifePoints = 1;
	//@Todo: set image and pos
}

Bonus::~Bonus()
{

}

void Bonus::update(Subject *sub)
{
	std::cout << "Bonus update" << std::endl;
	GameElement *elem = dynamic_cast<GameElement *>(sub);
	if (elem->getPosx() == this->posX && elem->getPosy() == this->posY)
	{
		--this->lifePoints;
		this->notify();
	}
}