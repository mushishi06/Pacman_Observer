#include "Map.hh"

Map::Map()
{

}

Map::~Map()
{

}

void	Map::update(Subject *sub)
{
	GameElement *elem = dynamic_cast<GameElement *>(sub);

	(void)elem;
}