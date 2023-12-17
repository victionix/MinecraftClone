#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <gfx/Window.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace util
{
	class Camera
	{
	public:
		Camera(glm::vec3 initialPos = glm::vec3(0.0f, 0.0f, 0.0f), glm::mat4 proj = glm::mat4(0.0F));
		virtual void update() {};
		
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		
		//in degrees
		float m_Yaw, m_Pitch;





	};
	

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(glm::vec3 initialPosition = glm::vec3(0.0f), float fov = 60.0f)
            : Camera(initialPosition)
        {
			m_Fov = fov;
			m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), gfx::Window::m_AspectRatio, 0.1f, 100.0f); };

		void update(glm::vec2 deltas);

		float m_Fov;
	};

};




#endif