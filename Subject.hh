#ifndef SUBJECT_HH_
# define SUBJECT_HH_

#include "IObserver.hh"

class Subject
{
public:
	virtual ~Subject() {};
	
	virtual void	notify() = 0;
	virtual void	attach(IObserver *obs) = 0;
	virtual void	detach(IObserver *obs) = 0;
};

#endif