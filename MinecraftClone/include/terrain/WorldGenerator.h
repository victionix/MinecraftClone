#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <terrain/ChunkMesh.h>

namespace terrain
{
	class WorldGenerator
	{
	public:
		WorldGenerator(uint64_t seed) : m_Seed(seed) {};

		void GenerateChunk(std::shared_ptr<terrain::Chunk> chunk);
		void GenerateChunk(terrain::Chunk* chunk);

	private:
		uint64_t m_Seed;
	};
}


#endif