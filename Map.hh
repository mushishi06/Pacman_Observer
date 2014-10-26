#ifndef MAP_HH_
# define MAP_HH_

#include "Subject.hh"
#include "GameElement.hh"

class Map : public IObserver
{
public:
	Map();
	~Map();
	virtual void update(Subject *sub);
	
public:
	char		map[12][12];
};

#endif