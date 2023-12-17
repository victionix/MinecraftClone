#include <terrain/ChunkMap.h>
#include <util/Log.h>
#include <algorithm>

terrain::ChunkMap::ChunkMap(const uint32_t renderDistance,const uint64_t seed)
	: m_WorldGenerator(seed), m_RenderDistance(renderDistance)
{
	createChunkInBounds();
	
	for (auto& x : m_ChunkInBounds)
	{
		for (uint32_t y = 0; y < terrain::Chunk::m_HeightLimit; y++)
		{
			glm::ivec3 position = glm::ivec3(x.x, y, x.y);
			addChunk(position);
		}
	}
	util::Log("Chunk map created");
	BuildChunks();
}

terrain::ChunkMap::~ChunkMap()
{
	m_Chunks.clear();
}



void terrain::ChunkMap::createChunkInBounds()
{
	for (int x = -int(m_RenderDistance); x <= int(m_RenderDistance); x++)
	{
		for (int y = -int(m_RenderDistance); y <= int(m_RenderDistance); y++)
		{
			if ((x * x + y * y) <= int(m_RenderDistance * m_RenderDistance))
			{
				m_ChunkInBounds.push_back(glm::ivec2(x, y));
			}
		}
	}
}

void terrain::ChunkMap::addChunk(const glm::ivec3 position)
{
	auto chunk = std::make_shared<terrain::ChunkMesh>(position);
	m_Chunks.emplace(position,std::move(chunk));
	m_WorldGenerator.GenerateChunk(m_Chunks[position]);
  
	for (uint16_t i = 0; i < 26; i++)
	{
		glm::ivec3 offset = position + terrain::Chunk::m_NeighboursOffset[i];
		if(auto accessNeighbour = find(offset))
		{
			m_Chunks[position]->m_Neighbours[i] = accessNeighbour;
			accessNeighbour->m_Neighbours[terrain::Chunk::m_InverseNeighboursOffset[i]] = m_Chunks[position];
		}
	}

}

void terrain::ChunkMap::BuildChunks()
{
	for (auto& chunk : m_Chunks)
	{
		chunk.second->Build();
	}
}
void terrain::ChunkMap::eraseChunk(glm::ivec3 position)
{
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
}
void terrain::ChunkMap::updateChunks(const glm::ivec2 oldCenterPosition, const glm::ivec2 newCenterPosition)
{
	//util::Log<glm::ivec2>(newCenterPosition, "Current chunk Position");
	std::vector<glm::ivec2> chunkToErase = {};
	std::vector<glm::ivec2> chunkToBuild = {};
	std::vector<glm::ivec2> chunkToRebuild = {};
	//Can use this following method since the render distance has not changed
	for(std::size_t i = 0; i < m_ChunkInBounds.size(); i++)
	{
		glm::ivec2 eraseOffset = m_ChunkInBounds[i] + oldCenterPosition-newCenterPosition;
		if ((eraseOffset.x*eraseOffset.x)+(eraseOffset.y*eraseOffset.y) > (m_RenderDistance * m_RenderDistance))
		{
			chunkToErase.push_back(m_ChunkInBounds[i] + oldCenterPosition);
		}
		glm::ivec2 buildOffset = m_ChunkInBounds[i] + newCenterPosition-oldCenterPosition;
		if ((buildOffset.x*buildOffset.x)+(buildOffset.y*buildOffset.y) > (m_RenderDistance * m_RenderDistance))
		{
			chunkToBuild.push_back(m_ChunkInBounds[i] + newCenterPosition);
		}
		else
		{
			chunkToRebuild.push_back(m_ChunkInBounds[i] + newCenterPosition);
		}
	}
	for (auto& x : chunkToBuild)
	{
		for (int y = 0; y < terrain::Chunk::m_HeightLimit; y++)
		{
			addChunk(glm::ivec3(x.x, y, x.y));
		}
	}
	for (std::size_t i = 0; i < chunkToBuild.size(); i++)
	{	
		for (int y = 0; y < terrain::Chunk::m_HeightLimit; y++)
		{
			glm::ivec3 position = glm::ivec3(chunkToBuild[i].x,y, chunkToBuild[i].y);
			m_Chunks[position]->Build();
		}
	}	
	for (std::size_t i = 0; i < chunkToErase.size(); i++)
	{
		for (int y = 0; y < terrain::Chunk::m_HeightLimit; y++)
		{
			glm::ivec3 position = glm::ivec3(chunkToErase[i].x, y, chunkToErase[i].y);
			eraseChunk(position);
		}
	}
	for (std::size_t i = 0; i < chunkToRebuild.size(); i++)
	{
		for (int y = 0; y < terrain::Chunk::m_HeightLimit; y++)
		{
			m_Chunks[glm::ivec3(chunkToRebuild[i].x, y, chunkToRebuild[i].y)]->Build();
		}
	}
	
}

void terrain::ChunkMap::updateRenderDistance(const uint32_t newRenderDistance)
{

}

void terrain::ChunkMap::RenderChunks(gfx::TextureArray& textureArray, gfx::Shader& shader,glm::mat4 view, glm::mat4 projection, glm::vec4 grassColor)
{
	for (auto& chunk : m_Chunks)
	{
		if((chunk.second->m_IsBuild)&&(!chunk.second->m_IsEmpty))
		{
			chunk.second->Render(textureArray, shader,view, projection, grassColor);
		}
	}
}

std::shared_ptr<terrain::ChunkMesh> terrain::ChunkMap::find(const glm::ivec3 pos)
{
	auto it = m_Chunks.find(pos);
	if (it == m_Chunks.end()) { return nullptr; }
	return it->second;
}

Block* terrain::ChunkMap::getBlock(const glm::ivec3 position)
{
	glm::ivec3 chunkPos = position / terrain::Chunk::m_Size;
	if (m_Chunks.find(position) != m_Chunks.end())
	{
		return m_Chunks[chunkPos]->getBlock(position);
	}
	return nullptr;
}



