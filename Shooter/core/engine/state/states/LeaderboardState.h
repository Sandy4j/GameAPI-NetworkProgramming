#ifndef LEADERBOARDSTATE_H
#define LEADERBOARDSTATE_H

#include "state.h"
#include "../../Integration/Integration.h"
#include <vector>

class LeaderboardState : public state
{
public:
	LeaderboardState();
	~LeaderboardState() = default;

public:
	virtual void iEnter() override;
	virtual void iUpdateLogic() override;
	virtual void iUpdateRenderObject() override;
	virtual void iUpdateRenderUI() override;
	virtual void iExit() override;

private:
	std::vector<GameAPI::LeaderboardEntry> leaderboardData;
	bool isLoading;
	std::string errorMessage;
	
	void LoadLeaderboard();
};

#endif
