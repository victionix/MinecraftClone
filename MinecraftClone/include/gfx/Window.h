#ifndef WINDOW_H
#define WINDOW_H
#define  GLEW_STATIC 1

#include <gfx/Debug/Debug.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>
#include <string>
#include <glm/glm.hpp>

namespace gfx
{
	class Window
	{
	public:
		Window(GLint width, GLint height,std::string title);
		~Window();

		void init();
		void clear();

		void update();

		static GLFWwindow* getWindow();



	private:
		static GLFWwindow* m_Window;
		bool isCreated = false;
	public:
		static GLint m_Width, m_Height;
		static float m_AspectRatio;
		std::string m_Title;

	};


	class Input
	{
	public:
		static bool isKeyPressed(int key);
		static bool isMouseButtonpressed(int key);
		static glm::vec2 getMousePosition();
	};
};

#endif