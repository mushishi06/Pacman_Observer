#include "Cycle.hh"

Cycle::Cycle()
{

}

Cycle::~Cycle()
{

}


Cycle::checkEatable()
{
  for (std::list<int>::iterator it = monster.begin(); it != monster.end(); it++)
    {
      if (it->eatable)
	it->decrease();
    }
}

