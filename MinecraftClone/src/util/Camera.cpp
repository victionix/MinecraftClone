#include <util/Camera.h>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gfx/Window.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


util::Camera::Camera(glm::vec3 initialPos, glm::mat4 proj)
{
    m_ProjectionMatrix = proj;

    m_Position = initialPos;
    m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_Yaw = 0.0f;
    m_Pitch = 0.0f;
}

void util::PerspectiveCamera::update(glm::vec2 deltas)
{
    m_Yaw += deltas.x;
    m_Pitch += deltas.y;

    m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

    m_Front = glm::normalize(glm::vec3(cos(glm::radians(m_Yaw))* cos(glm::radians(m_Pitch)),
        sin(glm::radians(m_Pitch)),
        sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch))));

}
