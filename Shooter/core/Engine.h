#ifndef ENGINE_H
#define ENGINE_H

struct GLFWwindow;

class Engine
{
public:
	static void INIT();
	static void UPDATE();
	static void SHUTDOWN();

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
};

#endif