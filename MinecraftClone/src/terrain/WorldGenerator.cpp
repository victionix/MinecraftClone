#include <terrain/WorldGenerator.h>
#include <Blocks/AllBlocks.h>


void terrain::WorldGenerator::GenerateChunk(std::shared_ptr<terrain::ChunkMesh> chunk)
{
    glm::ivec3 position = glm::ivec3(0);

    for (position.y = 0; position.y < terrain::Chunk::m_Size.x; position.y++)
    {
        for (position.z = 0; position.z < terrain::Chunk::m_Size.y; position.z++)
        {
            for (position.x = 0; position.x < terrain::Chunk::m_Size.y; position.x++)
            {
                if (position.y+chunk->m_Position.y == 0)
                {
                    chunk->setBlock(position, std::make_unique<Dirt>());
                }
                else
                {
                    chunk->setBlock(position, nullptr);
                }
            }
        }
    }

    chunk->setBlock(glm::ivec3(0, 2, 0), std::make_unique<Dirt>());
}

void terrain::WorldGenerator::GenerateChunk(terrain::ChunkMesh* chunk)
{
    glm::ivec3 position = glm::ivec3(0);

    for (position.y = 0; position.y < terrain::Chunk::m_Size.x; position.y++)
    {
        for (position.z = 0; position.z < terrain::Chunk::m_Size.y; position.z++)
        {
            for (position.x = 0; position.x < terrain::Chunk::m_Size.y; position.x++)
            {
                if (position.y + chunk->m_Position.y == 0)
                {
                    chunk->setBlock(position, std::make_unique<Dirt>());
                }
                else
                {
                    chunk->setBlock(position, nullptr);
                }
            }
        }
    }

    chunk->setBlock(glm::ivec3(0, 2, 0), std::make_unique<Dirt>());
}

