#include <stdexcept>
#include "Map.hh"

Map::Map(const std::string map, const int sizeX, const int sizeY)
	: _name("Map")
{
	initialize(map, sizeX, sizeY);
}

Map::~Map()
{
}

std::string const &Map::getName() const
{
	return (this->_name);
}

void	Map::update(Subject *sub)
{
	GameElement *elem = dynamic_cast<GameElement *>(sub);

	if (_map[elem->getPosy() * _sizeX + elem->getPosx()] == '#') {
		std::cerr << "GameElement '" << elem->getName() <<"' is inside a wall !" << std::endl;
		throw std::logic_error("Invalid position"); 
	}
}

void	Map::initialize(const std::string map, const int sizeX, const int sizeY) {
	_map = std::string(map);
	_sizeX = sizeX;
	_sizeY = sizeY;
}


/*
 *	GETTERS
*/
const std::string	Map::getMap() const {
	return (_map);
}
char				Map::getCell(int x, int y) const {
	return (_map[y * _sizeX + x]);
}
int					Map::getWidth() const {
	return (_sizeX);
}
int					Map::getHeight() const {
	return (_sizeY);
}