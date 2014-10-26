#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>      // std::srand
#include "GameElement.hh"
#include "Bonus.hh"
#include "Map.hh"
#include "Player.hh"
#include "Monster.hh"

int main()
{
	std::srand(unsigned(std::time(0)));
	std::cout << "SALUT" << std::endl;
	std::string myMap = "#############################............##............##.####.#####.##.#####.####.##o####.#####.##.#####.####o##.####.#####.##.#####.####.##..........................##.####.##.########.##.####.##.####.##.########.##.####.##......##....##....##......#######.##### ## #####.############.##### ## #####.########.....##          ##.....####.###.## ###++### ##.###.####.###.## #++++++# ##.###.####o....   #++++++#   ....o####.###.## #++++++# ##.###.####.###.## ######## ##.###.####.....##          ##.....########.## ######## ##.############.## ######## ##.#######............##............##.####.#####.##.#####.####.##.####.#####.##.#####.####.##o..##................##..o####.##.##.########.##.##.######.##.##.########.##.##.####......##....##....##......##.##########.##.##########.##.##########.##.##########.##..........................#############################";
	Map	map(myMap, 28, 31);
	Bonus bonus(0, 0, "", "Bonus 1");
	Bonus b2(1, 1, "", "Bonus 2");
	Player p(2, 2, "", "Player 1");
	Monster m(3, 11, "", "Shadow");


	m.attach(&map);

	bonus.attach(&b2);
	bonus.notify();
	bonus.detach(&b2);

	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	m.move();
	std::cout << m << std::endl << std::endl;
	

	p.detach(&map);
	return (0);
}