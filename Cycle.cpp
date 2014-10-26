#include "Cycle.hh"

Cycle::Cycle()
{

}

Cycle::~Cycle()
{

}


void	Cycle::checkEatable()
{
  for (std::list<Monster>::iterator it = monster.begin(); it != monster.end(); it++)
    {
      if (it->getEatable())
	it->decrease();
    }
}

