#include <GLFW/glfw3.h>

#include "GameManager.h"

#include "InputManager.h"

void InputManager::UpdateInputAction()
{
    UpdateKeyBindings(GameManager::GetInstance().GetGameState().GetEnumState(ETrasition::eCurrent));
    UpdateMouseBindings(GameManager::GetInstance().GetGameState().GetEnumState(ETrasition::eCurrent));
}

void InputManager::InvokeBinding(const auto& bind, EInputEventType type)
{
    if (bind.actionCommand[int(type)]) bind.actionCommand[int(type)]->Execute();
    if (bind.functionCommand_f[int(type)]) bind.functionCommand_f[int(type)]();
}

void InputManager::UpdateKeyBindings(EGameState turn)
{
    switch (turn)
    {
    case EGameState::eMainMenu:
        mKeyBindings = mMainMenuKeyBindings;
        break;
    case EGameState::eGameplay:
        mKeyBindings = mGameplayKeyBindings;
        break;
    case EGameState::ePauseMenu:
        mKeyBindings = mPauseMenuKeyBindings;
        break;
    case EGameState::eGameOver:
        mKeyBindings = mGameOverKeyBindings;
        break;
    case EGameState::eNone:
        break;
    default:
        break;
    }
}

bool InputManager::IsKeyDown(int key)
{
	return !mPreviousKeys[key] && mCurrentKeys[key];
}

bool InputManager::IsKeyHold(int key)
{
	return mPreviousKeys[key] && mCurrentKeys[key];
}

bool InputManager::IsKeyReleased(int key)
{
	return mPreviousKeys[key] && !mCurrentKeys[key];
}

void InputManager::UpdateMouseBindings(EGameState turn)
{
    switch (turn)
    {
    case EGameState::eMainMenu:
        mMouseBindings.clear();
        break;
    case EGameState::eGameplay:
        mMouseBindings = mGameplayMouseBindings;
        break;
    case EGameState::ePauseMenu:
        mMouseBindings.clear();
        break;
    case EGameState::eGameOver:
        mMouseBindings.clear();
        break;
    case EGameState::eNone:
        break;
    default:
        break;
    }
}

bool InputManager::IsMouseDown(int key)
{
    return !mPreviousMouses[key] && mCurrentMouses[key];
}

bool InputManager::IsMouseHold(int key)
{
    return mPreviousMouses[key] && mCurrentMouses[key];
}

bool InputManager::IsMouseReleased(int key)
{
    return mPreviousMouses[key] && !mCurrentMouses[key];
}

void InputManager::iInit()
{
    UpdateInputAction();
}

void InputManager::iUpdate()
{
    mPreviousKeys = mCurrentKeys;

    for (int key = 0; key < GLFW_KEY_LAST; ++key)
    {
        mCurrentKeys[key] = glfwGetKey(GameManager::GetInstance().GetWindow(), key) == GLFW_PRESS;

        if (mKeyBindings.count(key))
        {
            const auto& binding = mKeyBindings[key];

            if (IsKeyDown(key)) InvokeBinding(binding, EInputEventType::ePress);
            if (IsKeyHold(key)) InvokeBinding(binding, EInputEventType::eHold);
            if (IsKeyReleased(key)) InvokeBinding(binding, EInputEventType::eRelease);
        }
    }

    mPreviousMouses = mCurrentMouses;

    for (int mouse = 0; mouse < GLFW_MOUSE_BUTTON_LAST; ++mouse)
    {
        mCurrentMouses[mouse] = glfwGetMouseButton(GameManager::GetInstance().GetWindow(), mouse) == GLFW_PRESS;

        if (mMouseBindings.count(mouse))
        {
            const auto& binding = mMouseBindings[mouse];

            if (IsMouseDown(mouse)) InvokeBinding(binding, EInputEventType::ePress);
            if (IsMouseHold(mouse)) InvokeBinding(binding, EInputEventType::eHold);
            if (IsMouseReleased(mouse)) InvokeBinding(binding, EInputEventType::eRelease);
        }
    }
}

void InputManager::iShutdown()
{

}
