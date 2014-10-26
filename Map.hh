#ifndef MAP_HH_
# define MAP_HH_

#include "Subject.hh"
#include "GameElement.hh"

class Map : public IObserver
{
public:
	Map(const std::string map, const int size_x, const int size_y);
	~Map();
	virtual void		update(Subject *sub);
	virtual std::string const &getName() const;

	const std::string	getMap() const;
	char				getCell(int x, int y) const;
	int					getWidth() const;
	int					getHeight() const;

protected:
	void			initialize(const std::string map, const int sizeX, const int sizeY);
	std::string		_name;
	std::string		_map;
	int				_sizeX;
	int				_sizeY;
};

#endif