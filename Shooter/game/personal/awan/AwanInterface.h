#ifndef AWANINTERFACE_H
#define AWANINTERFACE_H

class AwanInterface
{
public:
	AwanInterface() = default;
	~AwanInterface() = default;

public:
	virtual void IAwanStart() = 0;
	virtual void IAwanUpdate() = 0;
};

#endif
