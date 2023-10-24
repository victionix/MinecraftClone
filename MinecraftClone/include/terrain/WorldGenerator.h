#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <terrain/Chunkmesh.h>

namespace terrain
{
	class WorldGenerator
	{
	public:
		WorldGenerator(uint64_t seed) : m_Seed(seed) {};

		void GenerateChunk(std::shared_ptr<terrain::ChunkMesh> chunk);
		void GenerateChunk(terrain::ChunkMesh* chunk);

	private:
		uint64_t m_Seed;
	};
}


#endif