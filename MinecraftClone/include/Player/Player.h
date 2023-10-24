#ifndef PLAYER_H
#define PLAYER_H

#include <util/Camera.h>
#include <vector>

class Player
{
public:
	Player(glm::vec3 startPosition = glm::ivec3(0));

	void update(float deltaTime);
	void updateChunkPos();

private:
	glm::vec2 m_MouseLastPos;
	float m_Sensivity = 0.1f;
	bool m_ShowGeometry = false;

	bool firstMouse = true;
public:
	util::PerspectiveCamera m_Cam;
	glm::ivec2 m_ChunkPos;

};

#endif

