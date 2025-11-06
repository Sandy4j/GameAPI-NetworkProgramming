#ifndef MANUKINTERFACE_H
#define MANUKINTERFACE_H

class ManukInterface
{
public:
	ManukInterface() = default;
	~ManukInterface() = default;

public:
	virtual void IManukStart() = 0;
	virtual void IManukUpdate() = 0;
};

#endif
