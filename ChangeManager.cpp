#include "GameElement.hh"
#include "ChangeManager.hh"

ChangeManager* ChangeManager::_instance = 0;


ChangeManager::ChangeManager()
{
	std::cerr << "Create ChangeManager" << std::endl;
}

ChangeManager::~ChangeManager()
{
	std::cerr << "Destroy ChangeManager" << std::endl;
}

/*
* Singleton design pattern
*/
ChangeManager* ChangeManager::Instance ()
{
    if (_instance == 0)
    {
        _instance = new ChangeManager();
    }
    return _instance;
}

void	ChangeManager::Register(Subject *elem, IObserver *obs)
{
	/*@TODO: Check if obs is already on the list*/
	this->observerMap[elem].push_front(obs);
}

void	ChangeManager::Unregister_all(Subject *elem)
{
	std::map<Subject *, std::list<IObserver *> >::iterator it_map;

	it_map = this->observerMap.find(elem);
	if (it_map != this->observerMap.end())
	{
		std::list<IObserver *>::iterator it;
		for (it = it_map->second.begin(); it != it_map->second.end(); ++it)
		{
			it = it_map->second.erase(it);
			if (it == it_map->second.end())
				break;
		}
		this->observerMap.erase(it_map);
		std::cerr << "Element observer not found in map" << std::endl;
	}
	else
	{
		std::cerr << "Element subject not found in map" << std::endl;
	}
}

void	ChangeManager::Unregister(Subject *elem, IObserver *obs)
{
	std::map<Subject *, std::list<IObserver *> >::iterator it_map;

	it_map = this->observerMap.find(elem);
	if (it_map != this->observerMap.end())
	{
		std::list<IObserver *>::iterator it;
		for (it = it_map->second.begin(); it != it_map->second.end(); ++it)
		{
			if (*it == obs)
			{
				it_map->second.erase(it);
				if (it_map->second.empty())
				{
					this->observerMap.erase(it_map);
				}
				return ;
			}
		}
		std::cerr << "Element observer not found in map" << std::endl;
	}
	else
	{
		std::cerr << "Element subject not found in map" << std::endl;
	}
}

void	ChangeManager::notify(Subject *sub)
{
 	std::cerr << "ChangeManager will notify the observers of the subject" << std::endl;
	std::map<Subject *, std::list<IObserver *> >::iterator it_map;

	it_map = this->observerMap.find(sub);
	if (it_map != this->observerMap.end())
	{
		GameElement *elem = dynamic_cast<GameElement *>(it_map->first);
		std::cerr << "subject " << elem->getName() << " notifies" << std::endl;
		std::list<IObserver *>::iterator it;

		std::cerr << "map list to notify" << std::endl;
		for (it = it_map->second.begin(); it != it_map->second.end(); ++it)
		{
			std::cerr << "Observer " << (*it)->getName() << std::endl;
		}

		for (it = it_map->second.begin(); it != it_map->second.end(); ++it)
		{
			std::cerr << "Observer " << (*it)->getName() << std::endl;
			(*it)->update(sub);
		}
	}
	else
	{
		std::cerr << "Element subject not found in map" << std::endl;
	}
}
