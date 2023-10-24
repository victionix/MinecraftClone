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
		ChunkMap(uint32_t renderDistance=2, uint64_t seed = 0);

		void createChunkInBounds();
		void addChunk(const glm::ivec3 position, std::unique_ptr<ChunkMesh>& chunk);
		void BuildChunks();

		void BuildNeighboursChunks(const glm::ivec3 position);
		void updateChunks(const glm::ivec2 oldCenterPosition,const glm::ivec2 newCenterPosition);
		void updateRenderDistance(const uint32_t newRenderDistance);

		void RenderChunks(gfx::TextureArray& textureArray, gfx::Shader& shader,glm::mat4 view, glm::mat4 projection, glm::vec4 grassColor);

		Block* getBlock(const glm::ivec3 getBlock);

		std::shared_ptr<terrain::ChunkMesh> find(const glm::ivec3 pos);


	private:
		terrain::WorldGenerator m_WorldGenerator;

		std::unordered_map<glm::ivec3, std::shared_ptr<terrain::ChunkMesh>> m_Chunks;
		uint32_t m_RenderDistance;

		std::vector<glm::ivec2> m_ChunkInBounds;
			
	};
};


#endif