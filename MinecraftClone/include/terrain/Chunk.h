#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <glm/glm.hpp>
#include <memory>
#include <Blocks/Block.h>
#include <functional>
#include <Blocks/Dirt.h>




//Forward declaration of the ChunkMap class
namespace terrain {
	class ChunkMap;
}

namespace terrain {
	class Chunk
	{
	public:
	Chunk(const glm::ivec3 chunkPos);

	Chunk(Chunk const&) = delete;
	Chunk& operator=(Chunk const&) = delete;


	Block* getBlock(const glm::ivec3 pos);

	void setBlock(const glm::ivec3 pos, std::unique_ptr<Block> block);

	void setNeighbour(const uint32_t index, std::shared_ptr<Chunk>& neighbour) { m_Neighbours[index] = neighbour; };

	SolidNeighBours getBlockNeighBours(const glm::ivec3 position);

	inline bool isInBound(const glm::ivec3 position, const glm::ivec3 chunkPosition) {
		if ((position.x >= (chunkPosition.x + m_Size.x)) ||
			(position.x < chunkPosition.x) ||
			(position.y >= (chunkPosition.y + m_Size.y)) ||
			(position.y < chunkPosition.y) ||
			(position.z >= (chunkPosition.z + m_Size.z)) ||
			(position.z < chunkPosition.z))
		{
			return false;
		}
		return true;
	}

	inline uint32_t getCorrectOffset(glm::ivec3 position) { 
		for (uint16_t i = 0; i < 3; i++)
		{
			position[i] = position[i] % m_Size[i];
			if (position[i] < 0)
			{
				position[i] += m_Size[i];
			}
		}
		return position.x + position.z * m_Size.x + position.y * m_Area;
	};

	public:
		static constexpr const  glm::ivec3 m_Size = glm::ivec3(16, 16, 16);
		static constexpr const uint32_t m_Area = m_Size.x * m_Size.z;
		static constexpr const uint32_t m_Volume = m_Size.x * m_Size.y * m_Size.z;

		//For Blocks and Chunks !!
		static const std::array<glm::ivec3, 26> m_NeighboursOffset;
		//For the neighbours set
		static const std::array<int16_t, 26> m_InverseNeighboursOffset;

		//=Absolute chunk Position in true form. So is = to chunkPos * m_Size since true chunkPosition will be in the hasmap
		glm::ivec3 m_Position;

	public:
		//Build Limit in Chunk Unit
		static const uint16_t m_HeightLimit = 8;
		static const uint16_t m_GlobalHeightLimit = m_HeightLimit * m_Size.y;
		std::array<std::weak_ptr<Chunk>, 26> m_Neighbours = {};

	protected:
		std::array<std::unique_ptr<Block>, m_Volume> m_Data;
		bool m_BlocksGenerated = false;


	private:
		static const std::unique_ptr<Dirt> m_OutOfBoundsSolidBlock;

	};
}

#endif // !CHUNK_H
