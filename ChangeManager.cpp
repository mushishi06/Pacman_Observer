#include "GameElement.hh"
#include "ChangeManager.hh"

ChangeManager* ChangeManager::_instance = 0;


ChangeManager::ChangeManager()
{
	std::cout << "Create ChangeManager" << std::endl;
}

ChangeManager::~ChangeManager()
{
	std::cout << "Destroy ChangeManager" << std::endl;
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
		std::cout << "Element observer not found in map" << std::endl;
	}
	else
	{
		std::cout << "Element subject not found in map" << std::endl;
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
		std::cout << "Element observer not found in map" << std::endl;
	}
	else
	{
		std::cout << "Element subject not found in map" << std::endl;
	}
}

void	ChangeManager::notify(Subject *sub)
{
 	std::cout << "ChangeManager will notify the observers of the subject" << std::endl;
	std::map<Subject *, std::list<IObserver *> >::iterator it_map;

	it_map = this->observerMap.find(sub);
	if (it_map != this->observerMap.end())
	{
		GameElement *elem = dynamic_cast<GameElement *>(it_map->first);
		std::cout << "subject " << elem->getName() << " notifies" << std::endl;
		std::list<IObserver *>::iterator it;

		std::cout << "map list to notify" << std::endl;
		for (it = it_map->second.begin(); it != it_map->second.end(); ++it)
		{
			std::cout << "BEGIN" << std::endl;
			std::cout << "Observer " << (*it)->getName() << std::endl;
			std::cout << "END" << std::endl;
		}

std::cout << "NOTIFY" << std::endl;
		for (it = it_map->second.begin(); it != it_map->second.end(); ++it)
		{
			std::cout << "BEGIN" << std::endl;
			std::cout << "Observer " << (*it)->getName() << std::endl;
			(*it)->update(sub);
			std::cout << "END" << std::endl;
		}
		std::cout << "EXIT" << std::endl;
	}
	else
	{
		std::cout << "Element subject not found in map" << std::endl;
	}
}
