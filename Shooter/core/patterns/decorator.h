#ifndef DECORATOR_H
#define DECORATOR_H

#include <iostream>
#include <memory>

template<typename Tclass>
class decorator : public Tclass
{
protected:
	decorator(std::unique_ptr<Tclass> class_) : base(std::move(class_)) {}

public:
	virtual ~decorator() = default;

protected:
	std::unique_ptr<Tclass> base;
};

#endif