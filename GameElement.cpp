#include "GameElement.hh"

GameElement::GameElement(std::string const &n, int points)
: nbPoints(points), name(n), eatable(true)
{
}

GameElement::~GameElement()
{
}

void	GameElement::notify()
{
	std::cout << "GameElement " << this->name << " notify" << std::endl;
	ChangeManager::Instance()->notify(this);
}

void	GameElement::attach(IObserver *obs)
{
	ChangeManager::Instance()->Register(this, obs);
}

void	GameElement::detach(IObserver *obs)
{
	ChangeManager::Instance()->Unregister(this, obs);
}

int			GameElement::getNbPoints() const
{
	return (this->nbPoints);
}

int			GameElement::getPosx() const
{
	return (this->posX);
}

int			GameElement::getPosy() const
{
	return (this->posY);
}

std::string	const &GameElement::getName() const
{
	return (this->name);
}

bool		GameElement::getEatable()  const
{
	return (this->eatable);
}

int			GameElement::getLifePoints() const
{
	return (this->lifePoints);
}
