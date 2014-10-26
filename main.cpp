#include <iostream>
#include "GameElement.hh"
#include "Bonus.hh"
#include "Map.hh"

int main()
{
	std::cout << "SALUT" << std::endl;
	Bonus bonus;
	Bonus b2;
	(void)Map	m;

	bonus.attach(&b2);
	bonus.notify();
	bonus.detach(&b2);

	return (0);
}