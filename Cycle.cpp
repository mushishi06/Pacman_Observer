#include <iostream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include "Cycle.hh"

Cycle::Cycle()
{
	static char moves[4] = {'t', 'f', 'g', 'h'};
	int i = 0;

	while (i < 4)
	{
		this->_authorizedMoves.push_back(moves[i]);
		++i;
	}

	tcgetattr(0, &this->_t); //get the current terminal I/O structure
    this->_t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(0, TCSANOW, &this->_t); //Apply the new settings
}

Cycle::~Cycle()
{
	tcgetattr(0, &this->_t); //get the current terminal I/O structure
    this->_t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(0, TCSANOW, &this->_t); //Apply the new settings
}

char Cycle::getUserInput() const
{
	char input;

	input = getchar();

	for (std::vector<char>::const_iterator it = this->_authorizedMoves.begin(); it != this->_authorizedMoves.end(); ++it)
	{
		if (*it == input)
			return (input);
	}
	std::cout << "wrong command " << input << std::endl;
	return ('\0');
}