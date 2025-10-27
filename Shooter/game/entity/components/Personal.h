#ifndef PERSONAL_H
#define PERSONAL_H

class Personal
{
public:
	Personal() = default;
	~Personal() = default;

public:
	virtual void IPersonalStart() = 0;
	virtual void IPersonalUpdate() = 0;
};

#endif
