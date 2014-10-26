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
