#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "TimeManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RenderManager.h"

#include "Engine.h"

void Engine::INIT()
{
    TimeManager* time_manager = &TimeManager::GetInstance();
    GameManager* game_manager = &GameManager::GetInstance();
    InputManager* input_manager = &InputManager::GetInstance();
    UIManager* ui_manager = &UIManager::GetInstance();
    RenderManager* render_manager = &RenderManager::GetInstance();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    game_manager->CreateMainWindow(1080, 1080);

    if (!game_manager->GetWindow())
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(game_manager->GetWindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, game_manager->GetSizeWindow().x, game_manager->GetSizeWindow().y);
    glfwSetFramebufferSizeCallback(game_manager->GetWindow(), Engine::framebuffer_size_callback);
    glfwSetKeyCallback(game_manager->GetWindow(), Engine::key_callback);

    render_manager->iInit();
    ui_manager->iInit();
    game_manager->iInit();
    time_manager->iInit();
    input_manager->iInit();
}

void Engine::UPDATE()
{
    TimeManager* time_manager = &TimeManager::GetInstance();
    GameManager* game_manager = &GameManager::GetInstance();
    InputManager* input_manager = &InputManager::GetInstance();
    UIManager* ui_manager = &UIManager::GetInstance();
    RenderManager* render_manager = &RenderManager::GetInstance();

    while (!glfwWindowShouldClose(game_manager->GetWindow()))
    {
        glfwPollEvents();

        time_manager->iUpdate();
        input_manager->iUpdate();
        game_manager->iUpdate();

        render_manager->iUpdate();
        ui_manager->iUpdate();

        glfwSwapBuffers(game_manager->GetWindow());

        if (glfwWindowShouldClose(game_manager->GetWindow()) && !game_manager->GetIsExit())
            glfwSetWindowShouldClose(game_manager->GetWindow(), GLFW_FALSE);
    }
}

void Engine::SHUTDOWN()
{
    TimeManager::GetInstance().iShutdown();
    GameManager::GetInstance().iShutdown();
    InputManager::GetInstance().iShutdown();
    UIManager::GetInstance().iShutdown();
    RenderManager::GetInstance().iShutdown();
    glfwTerminate();
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Engine::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F4 && (mods & GLFW_MOD_ALT) && action == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(win, GLFW_FALSE);
        return;
    }
}
