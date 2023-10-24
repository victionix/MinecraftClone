#include <Player/Player.h>
#include <gfx/Window.h>
#include <terrain/Chunk.h>

Player::Player(glm::vec3 startPosition)
	: m_Cam(startPosition)
{
    m_MouseLastPos = glm::vec2(gfx::Window::m_Width / 2.0f, gfx::Window::m_Height/2.0f);
	updateChunkPos();
}

void Player::update(float deltaTime)
{
	if (gfx::Input::isKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(gfx::Window::getWindow(), true); }

	if (gfx::Input::isKeyPressed(GLFW_KEY_C))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
    glm::vec2 mousePos = gfx::Input::getMousePosition();
    if (firstMouse)
    {
        mousePos = m_MouseLastPos;
        firstMouse = false;
    }


    glm::vec2 mouseDelta = glm::vec2(mousePos.x - m_MouseLastPos.x, m_MouseLastPos.y-mousePos.y) * m_Sensivity;
    m_MouseLastPos = mousePos;

    bool move = false;

    if ((mouseDelta.x != 0.0F) || (mouseDelta.y !=0.0f))
    {
        m_Cam.update(mouseDelta);
        move = true;
    }

    const float cameraSpeed = 4.5f * deltaTime;
    if (gfx::Input::isKeyPressed(GLFW_KEY_W))
    {
        m_Cam.m_Position += cameraSpeed * m_Cam.m_Front;
        move = true;
    }
    if (gfx::Input::isKeyPressed(GLFW_KEY_S))
    {
        m_Cam.m_Position -= cameraSpeed * m_Cam.m_Front;
        move = true;
    }
    if (gfx::Input::isKeyPressed(GLFW_KEY_A))
    {
        m_Cam.m_Position -= glm::normalize(glm::cross(m_Cam.m_Front, m_Cam.m_Up)) *
            cameraSpeed;
        move = true;
    }
    if (gfx::Input::isKeyPressed(GLFW_KEY_D))
    {
        m_Cam.m_Position += glm::normalize(glm::cross(m_Cam.m_Front, m_Cam.m_Up)) *
            cameraSpeed;
        move = true;
    }
    if (gfx::Input::isKeyPressed(GLFW_KEY_SPACE))
    {
        m_Cam.m_Position += m_Cam.m_Up * cameraSpeed;
        move = true;
    }
    if (gfx::Input::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        m_Cam.m_Position -= m_Cam.m_Up * cameraSpeed;
        move = true;
    }


    if (move)
    {
        m_Cam.m_ViewMatrix = glm::lookAt(m_Cam.m_Position, m_Cam.m_Position + m_Cam.m_Front, m_Cam.m_Up);
        updateChunkPos();
    }
}



void Player::updateChunkPos()
{
    m_ChunkPos.x = glm::floor(m_Cam.m_Position.x / (float)terrain::Chunk::m_Size.x);
	m_ChunkPos.y = glm::floor(m_Cam.m_Position.z / (float)terrain::Chunk::m_Size.z);
}
