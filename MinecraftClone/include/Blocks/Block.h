#ifndef BLOCK_H
#define BLOCK_H
 
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <memory>
#include <gfx/Vertex/Vertex.h>


enum BlockMeshType
{
	BLOCKMESH_NULL=0,
	BLOCKMESH_DEFAULT=1,
	BLOKMESH_CUSTOM=2,
};

enum BlockID
{
	AIR = 0,
	GRASS = 1,
	DIRT = 2,
	COBBLE = 3,
};

struct FacesTexturesId
{
	uint16_t BackFace;
	uint16_t FrontFace;
	uint16_t LeftFace;
	uint16_t RightFace;
	uint16_t BottomFace;
	uint16_t TopFace;
};


struct VisibleFaces
{
	bool BackFace;
	bool FrontFace;
	bool LeftFace;
	bool RightFace;
	bool BottomFace;
	bool TopFace;
};

struct SolidNeighBours
{
	std::array<bool, 26> neighbours;
};


struct MeshData
{
	std::vector<uint32_t> indices = {};
	std::vector<Vertex> vertices = {};
};


class Block
{
public:
	BlockID id = AIR;
	BlockMeshType mesh = BLOCKMESH_NULL;
	FacesTexturesId facesTextureId = {};
	bool _isStatic = true;



	Block() { };

	void BackFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position);
	void FrontFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position);
	void LeftFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position);
	void RightFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position);
	void BottomFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position);
	void TopFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position);

	void generateMesh(MeshData& mesh,SolidNeighBours neighbours, glm::ivec3 position);

};



#endif // !BLOCK_H
