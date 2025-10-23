#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <memory>
#include <functional>
#include "singleton.h"
#include "command.h"
#include "GameState.h"

enum class EInputEventType
{
	ePress,
	eHold,
	eRelease
};

struct CommandBinding
{
	std::shared_ptr<command> actionCommand[3] = { nullptr };
	std::function<void()> functionCommand_f[3] = { nullptr };
};

class InputManager : public singleton<InputManager>
{
public:
	InputManager() = default;
	~InputManager() = default;

public:
	void UpdateInputAction();

	template<typename TCommand>
	void BindKeyAction(int key, EInputEventType type, EGameState turn)
	{
		switch (turn)
		{
		case EGameState::eMainMenu:
			mMainMenuKeyBindings[key].actionCommand[(int)type] = std::make_shared<TCommand>();
			mMainMenuKeyBindings[key].functionCommand_f[(int)type];
			break;
		case EGameState::eGameplayPlayerOne:
			mPlayerOneKeyBindings[key].actionCommand[(int)type] = std::make_shared<TCommand>();
			mPlayerOneKeyBindings[key].functionCommand_f[(int)type];
			break;
		case EGameState::eGameplayPlayerTwo:
			mPlayerTwoKeyBindings[key].actionCommand[(int)type] = std::make_shared<TCommand>();
			mPlayerTwoKeyBindings[key].functionCommand_f[(int)type];
			break;
		case EGameState::ePauseMenu:
			mPauseMenuKeyBindings[key].actionCommand[(int)type] = std::make_shared<TCommand>();
			mPauseMenuKeyBindings[key].functionCommand_f[(int)type];
			break;
		case EGameState::eGameOver:
			mGameOverKeyBindings[key].actionCommand[(int)type] = std::make_shared<TCommand>();
			mGameOverKeyBindings[key].functionCommand_f[(int)type];
			break;
		}
	}

	void BindKeyFunction(std::function<void()> function, int key, EInputEventType type, EGameState turn)
	{
		switch (turn)
		{
		case EGameState::eMainMenu:
			mMainMenuKeyBindings[key].actionCommand[(int)type];
			mMainMenuKeyBindings[key].functionCommand_f[(int)type] = function;
			break;
		case EGameState::eGameplayPlayerOne:
			mPlayerOneKeyBindings[key].actionCommand[(int)type];
			mPlayerOneKeyBindings[key].functionCommand_f[(int)type] = function;
			break;
		case EGameState::eGameplayPlayerTwo:
			mPlayerTwoKeyBindings[key].actionCommand[(int)type];
			mPlayerTwoKeyBindings[key].functionCommand_f[(int)type] = function;
			break;
		case EGameState::ePauseMenu:
			mPauseMenuKeyBindings[key].actionCommand[(int)type];
			mPauseMenuKeyBindings[key].functionCommand_f[(int)type] = function;
			break;
		case EGameState::eGameOver:
			mGameOverKeyBindings[key].actionCommand[(int)type];
			mGameOverKeyBindings[key].functionCommand_f[(int)type] = function;
			break;
		}
	}

	void BindMouseFunction(std::function<void()> function, int key, EInputEventType type, EGameState turn)
	{
		switch (turn)
		{
		case EGameState::eGameplayPlayerOne:
			mPlayerOneMouseBindings[key].actionCommand[(int)type];
			mPlayerOneMouseBindings[key].functionCommand_f[(int)type] = function;
			break;
		case EGameState::eGameplayPlayerTwo:
			mPlayerTwoMouseBindings[key].actionCommand[(int)type];
			mPlayerTwoMouseBindings[key].functionCommand_f[(int)type] = function;
			break;
		}
	}

private:
	void InvokeBinding(const auto& bind, EInputEventType type);

	void UpdateKeyBindings(EGameState turn);
	bool IsKeyDown(int key);
	bool IsKeyHold(int key);
	bool IsKeyReleased(int key);

	void UpdateMouseBindings(EGameState turn);
	bool IsMouseDown(int key);
	bool IsMouseHold(int key);
	bool IsMouseReleased(int key);

private:
	std::unordered_map<int, CommandBinding> mMainMenuKeyBindings;
	std::unordered_map<int, CommandBinding> mGameOverKeyBindings;
	std::unordered_map<int, CommandBinding> mPauseMenuKeyBindings;
	std::unordered_map<int, CommandBinding> mPlayerOneKeyBindings;
	std::unordered_map<int, CommandBinding> mPlayerTwoKeyBindings;
	std::unordered_map<int, CommandBinding> mKeyBindings;
	std::unordered_map<int, bool> mCurrentKeys;
	std::unordered_map<int, bool> mPreviousKeys;

	std::unordered_map<int, CommandBinding> mPlayerOneMouseBindings;
	std::unordered_map<int, CommandBinding> mPlayerTwoMouseBindings;
	std::unordered_map<int, CommandBinding> mMouseBindings;
	std::unordered_map<int, bool> mCurrentMouses;
	std::unordered_map<int, bool> mPreviousMouses;

public:
	virtual void iInit() override;
	virtual void iUpdate() override;
	virtual void iShutdown() override;
};

#endif
