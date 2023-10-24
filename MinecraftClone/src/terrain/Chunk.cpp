#include <terrain/Chunk.h>
#include<Blocks/Dirt.h>
#include <util/Log.h>


const std::unique_ptr<Dirt> terrain::Chunk::m_OutOfBoundsSolidBlock = std::make_unique<Dirt>();


const std::array <glm::ivec3, 26> terrain::Chunk::m_NeighboursOffset =
{
	glm::ivec3(0, 0, 1), // 0
	glm::ivec3(0, 0,-1), // 1
	glm::ivec3(0, 1, 0), // 2
	glm::ivec3(0, 1, 1), // 3
	glm::ivec3(0, 1,-1), // 4
	glm::ivec3(0,-1, 0), // 5
	glm::ivec3(0,-1, 1), // 6
	glm::ivec3(0,-1,-1), // 7

	glm::ivec3(1, 0, 0), // 8
	glm::ivec3(1, 0, 1), // 9
	glm::ivec3(1, 0,-1), // 10
	glm::ivec3(1, 1, 0), // 11
	glm::ivec3( 1, 1, 1 ), // 12
	glm::ivec3( 1, 1,-1 ), // 13
	glm::ivec3( 1,-1, 0 ), // 14
	glm::ivec3( 1,-1, 1 ), // 15
	glm::ivec3( 1,-1,-1 ), // 16

	glm::ivec3( - 1, 0, 0 ), // 17
	glm::ivec3( - 1, 0, 1 ), // 18
	glm::ivec3( - 1, 0,-1 ), // 19
	glm::ivec3( - 1, 1, 0 ), // 20
	glm::ivec3( - 1, 1, 1 ), // 21
	glm::ivec3( - 1, 1,-1 ), // 22
	glm::ivec3( - 1,-1, 0 ), // 23
	glm::ivec3( - 1,-1, 1 ), // 24
	glm::ivec3( - 1,-1,-1 ), // 25
};

const std::array <int16_t, 26> terrain::Chunk::m_InverseNeighboursOffset =
{
  1, 0, 5, 7, 6, 2, 4, 3,
  17, 19, 18, 23, 25, 24, 20, 22, 21,
  8, 10, 9, 14, 16, 15, 11, 13, 12
};

terrain::Chunk::Chunk(const glm::ivec3 chunkPos)
{
	m_Position = chunkPos*m_Size;
}

Block* terrain::Chunk::getBlock(const glm::ivec3 pos)
{
	if (pos.y < 0)
	{
		return m_OutOfBoundsSolidBlock.get();
	}
	if (pos.y >= m_GlobalHeightLimit)
	{
		return nullptr;
	}

	for (std::size_t i = 0; i < 26; ++i) {
		if(isInBound(pos, m_Position + m_Size*m_NeighboursOffset[i]))
		{
			if (auto neigh = m_Neighbours[i].lock())
			{
				return neigh->getBlock(pos);
			}
			else {
				return m_OutOfBoundsSolidBlock.get();
			}
		}
	}

	int index = getCorrectOffset(pos);
	return m_Data[index].get();
}

void terrain::Chunk::setBlock(const glm::ivec3 pos, std::unique_ptr<Block> block)
{
	//assuming the position is in bounds
	int index = pos.x + pos.z*m_Size.x + pos.y * m_Area;
	m_Data[index] = std::move(block);

}

SolidNeighBours terrain::Chunk::getBlockNeighBours(glm::ivec3 position)
{
	SolidNeighBours SolidBlockNeighbours = {};
	for (uint8_t i = 0; i < 26; i++)
	{
		glm::ivec3 offset = position + m_NeighboursOffset[i];
		if (offset.y >= m_GlobalHeightLimit)
		{
			SolidBlockNeighbours.neighbours[i] = true;
		}
		else
		{
				Block* blockNeighbour = getBlock(offset);
				if (blockNeighbour != nullptr)
				{
					SolidBlockNeighbours.neighbours[i] = (blockNeighbour->mesh == BLOCKMESH_DEFAULT) ? true : false;
				}
				else {
					SolidBlockNeighbours.neighbours[i] = false;
				}
		}
	}
	return SolidBlockNeighbours;
}



