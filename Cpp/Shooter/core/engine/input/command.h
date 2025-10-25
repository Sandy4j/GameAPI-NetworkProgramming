#ifndef COMMAND_H
#define COMMAND_H

class command
{
protected:
	command() = default;

public:
	virtual ~command() = default;

public:
	virtual void Execute() = 0;
};

#endif