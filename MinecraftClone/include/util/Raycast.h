#ifndef RAYCAST_H
#define RAYCAST_H

#include <glm/glm.hpp>
#include <Blocks/Block.h>
#include <terrain/World.h>
struct CastResult
{
	bool sucess;
	float dist;
	Block* block;
	glm::vec3 position;
};
namespace util
{
	class Raycast
	{
	public:
		Raycast(uint32_t maxDist) :m_MaxDistance(maxDist) {};


		CastResult rayCast(glm::vec3 pos, glm::vec3 rayDirection);


	private:
		uint32_t m_MaxDistance;


	};
};

#endif // ! RAYCAST_H
