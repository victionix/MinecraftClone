#include <terrain/World.h>

Block* World::getBlock(const glm::ivec3 pos)
{
    return m_ChunkMap.getBlock(pos);
}
