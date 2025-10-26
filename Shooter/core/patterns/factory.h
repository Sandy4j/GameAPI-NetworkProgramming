#ifndef FACTORY_H
#define FACTORY_H

#include <memory>

template<typename Tclass>
class factory
{
protected:
	factory() = default;

public:
	virtual ~factory() = default;

public:
	virtual std::unique_ptr<Tclass> iCreate() = 0;
};

#endif