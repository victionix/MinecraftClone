#include <gfx/Window.h>
#include <util/Log.h>
#include <stdio.h>

GLFWwindow* gfx::Window::m_Window = nullptr;
GLint gfx::Window::m_Width = 0;
GLint gfx::Window::m_Height= 0;
float gfx::Window::m_AspectRatio = 0;

gfx::Window::Window(GLint width, GLint height,std::string title)
{
    m_Width = width;
    m_Height = height;
    m_Title = title;
    m_AspectRatio = ((float)m_Width) / ((float)m_Height);
	init();
}

gfx::Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void err(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void gfx::Window::init()
{

    glfwSetErrorCallback(err);
	if (!glfwInit())
	{

        fprintf(stderr, "GLFW failed to initialize.");

        int code = glfwGetError(NULL);

        util::Log<int>(code,"Code ");

        glfwTerminate();


		abort();
	}

    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        util::Log("WARNING cannot create window");
        abort();
    }

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(0);

    GLenum err = glewInit();
    if (err != GLEW_OK) { util::Log<const GLubyte*>(glewGetErrorString(err),""); abort(); }
    util::Log<const GLubyte*>(glGetString(GL_VERSION), "OpenGl version :");
    
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLCall(glEnable(GL_DEPTH_TEST));

//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_BLEND);

    isCreated = true;
}

void gfx::Window::clear()
{

	GLCall(glClearColor(0.4f, 0.2f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}


void gfx::Window::update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

GLFWwindow* gfx::Window::getWindow()
{
    return m_Window;
}

bool gfx::Input::isKeyPressed(int key)
{
    auto state = glfwGetKey(gfx::Window::getWindow(), key);
    return state == GLFW_PRESS;
}

bool gfx::Input::isMouseButtonpressed(int key)
{
    auto state = glfwGetMouseButton(gfx::Window::getWindow(), key);
    return state == GLFW_PRESS;
}

glm::vec2 gfx::Input::getMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(gfx::Window::getWindow(), &xpos, &ypos);
    return glm::vec2(float(xpos), float(ypos));
}

