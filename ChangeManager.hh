#ifndef CHANGEMANAGER_HH_
# define CHANGEMANAGER_HH_

#include <map>
#include <list>
#include <iostream>
#include "Subject.hh"

class ChangeManager
{
public:
    static ChangeManager* Instance();

	~ChangeManager();
	void	Register(Subject *elem, IObserver *obs);
	void	Unregister(Subject *elem, IObserver *obs);
	void	Unregister_all(Subject *elem);
	void	notify(Subject *sub);

protected:
    ChangeManager();
        
private:
	static ChangeManager* _instance;
	std::map<Subject *, std::list<IObserver *> >	observerMap;
};

#endif