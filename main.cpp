#include <iostream>
#include "GameElement.hh"
#include "Bonus.hh"
#include "Map.hh"
#include "Player.hh"

int main()
{
	std::cout << "SALUT" << std::endl;
	Bonus bonus(0, 0, "", "Bonus 1");
	Bonus b2(1, 1, "", "Bonus 2");
	Player p(2, 2, "", "Player 1");

	bonus.attach(&b2);
	bonus.notify();
	bonus.detach(&b2);

	std::cout << p << std::endl;

	p.move(4, 4);
	p.changeDirection(ACharacter::DOWN);

	std::cout << p << std::endl;
	
	return (0);
}