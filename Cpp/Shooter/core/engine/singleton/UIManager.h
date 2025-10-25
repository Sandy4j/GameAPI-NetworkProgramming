#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "singleton.h"

class UIManager : public singleton<UIManager>
{
public:
	UIManager() = default;
	~UIManager() = default;

public:
	virtual void iInit() override;
	virtual void iUpdate() override;
	virtual void iShutdown() override;
};

#endif