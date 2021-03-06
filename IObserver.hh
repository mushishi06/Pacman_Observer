#ifndef IOBSERVER_HH_
# define IOBSERVER_HH_

class Subject;

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void update(Subject*subj) = 0;
	virtual std::string const &getName() const = 0;
};

#endif