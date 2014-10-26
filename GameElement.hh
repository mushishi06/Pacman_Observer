#ifndef GAMEELEMENT_HH_
# define GAMEELEMENT_HH_

#include <string>
#include <iostream>
#include "ChangeManager.hh"

class GameElement : public IObserver, public Subject
{
public:
	GameElement(std::string const &name = "Generic", int nbPoints = 0);
	virtual ~GameElement();
	virtual void update(Subject *sub) = 0;
	virtual void	notify();
	virtual void	attach(IObserver *obs);
	virtual void	detach(IObserver *obs);

	int			getNbPoints() const;
	int			getPosx() const;
	int			getPosy() const;
	std::string	const &getName() const;

protected:
	int			nbPoints;
	std::string	name;
	bool		eatable;
	int			lifePoints;
	std::string image;
	int 		posX;
	int 		posY;
};

#endif