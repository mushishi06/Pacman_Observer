#include <iostream>
#include "GameElement.hh"
#include "Bonus.hh"
#include "Map.hh"

int main()
{
	std::cout << "SALUT" << std::endl;
	Bonus bonus(0, 0, "", 1, "Bonus 1");
	Bonus b2(1, 1, "", 1, "Bonus 2");

	bonus.attach(&b2);
	bonus.notify();
	bonus.detach(&b2);

	return (0);
}