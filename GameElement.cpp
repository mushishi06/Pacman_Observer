#include "GameElement.hh"

GameElement::GameElement(std::string const &n, int points)
: nbPoints(points), name(n)
{
	std::cout << "Create " << n << std::endl;
}

GameElement::~GameElement()
{
	std::cout << "Destroy " << this->name << std::endl;
}
	
void	GameElement::notify()
{
	std::cout << "GameElement " << this->name << " notify" << std::endl;
	ChangeManager::Instance()->notify(this);
}
	
void	GameElement::attach(IObserver *obs)
{
	std::cout << "attach to " << this->name << std::endl;
	ChangeManager::Instance()->Register(this, obs);
}

void	GameElement::detach(IObserver *obs)
{
	std::cout << "detach from " << this->name << std::endl;
	ChangeManager::Instance()->Unregister(this, obs);
}

int			GameElement::getNbPoints()
{
	return (this->nbPoints);
}

int			GameElement::getPosx()
{
	return (this->posX);
}

int			GameElement::getPosy()
{
	return (this->posY);
}