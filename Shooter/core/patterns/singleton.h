#ifndef SINGLETON_H
#define SINGLETON_H

template <typename Tclass>
class singleton
{
protected:
	singleton() = default;

public:
	virtual ~singleton() = default;

public:
	virtual void iInit() = 0;
	virtual void iUpdate() = 0;
	virtual void iShutdown() = 0;

public:
	static Tclass& GetInstance()
	{
		static Tclass instance;
		return instance;
	}

	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;
};

#endif