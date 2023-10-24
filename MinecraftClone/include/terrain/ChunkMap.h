#ifndef CHUNK_MAP_H
#define CHUNK_MAP_H

#include <unordered_map>
#include <vector>
#include <terrain/ChunkMesh.h>
#include <terrain/WorldGenerator.h>

#include <terrain/hashGlmIvec3.h>

namespace terrain
{
	class ChunkMap
	{
	public:
		ChunkMap(uint32_t renderDistance=1, uint64_t seed = 0);
		~ChunkMap();

		void createChunkInBounds();
		void addChunk(const glm::ivec3 position);
		void BuildChunks();

		void eraseChunk(glm::ivec3 position) 
		{
			//m_Chunks[position]->free();
			//m_Chunks[position].reset();
			//m_Chunks[position] = nullptr;
			m_Chunks.erase(position);
			for (uint16_t i = 0; i < 26; i++)
			{
				glm::ivec3 offset = position + terrain::Chunk::m_NeighboursOffset[i];
				auto accessNeighbour = find(offset);
				if (accessNeighbour != nullptr)
				{
					accessNeighbour->m_Neighbours[terrain::Chunk::m_InverseNeighboursOffset[i]].reset();
				}
			}
		};

		void updateChunks(const glm::ivec2 oldCenterPosition,const glm::ivec2 newCenterPosition);
		void updateRenderDistance(const uint32_t newRenderDistance);

		void RenderChunks(gfx::TextureArray& textureArray, gfx::Shader& shader,glm::mat4 view, glm::mat4 projection, glm::vec4 grassColor);

		Block* getBlock(const glm::ivec3 getBlock);

		std::shared_ptr<terrain::ChunkMesh> find(const glm::ivec3 pos);

		std::unordered_map<glm::ivec3, std::shared_ptr<terrain::ChunkMesh>, ivec3Hash, ivec3Hash> m_Chunks;
	private:
		terrain::WorldGenerator m_WorldGenerator;

		int32_t m_RenderDistance;

		std::vector<glm::ivec2> m_ChunkInBounds;
			
	};
};


#endif