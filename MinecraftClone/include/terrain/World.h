#ifndef WORLD_H
#define WORLD_H

#include <terrain/ChunkMap.h>
#include <Player/Player.h>

class World
{
public:
	static World& getInstance() { static World world; return world; };
	
	Block* getBlock(const glm::ivec3 pos);

	~World() { };

	void Render();


private:
	World() : m_ChunkMap(), m_Player() {};


public:
	terrain::ChunkMap m_ChunkMap;
	Player m_Player;


	

};

#endif
