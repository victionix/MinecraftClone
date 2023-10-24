#include <Blocks/Block.h>

void Block::BackFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position)
{
    indices.reserve(6);
    int latestIndex = 0;
    if (indices.size() > 0)
    {
        latestIndex += indices.back() + 1;
    }
    int insertIndices[6] = { latestIndex,latestIndex + 1,latestIndex + 2,latestIndex + 1,latestIndex,latestIndex + 3 };
    indices.insert(indices.end(), insertIndices, insertIndices + 6);
    vertices.reserve(4);
    Vertex insertVertex[4] = {
       Vertex(0.0f + position.x, 0.0f + position.y, 0.0f + position.z, 0.0f, 0.0f, facesTextureId.BottomFace),
       Vertex(1.0f + position.x, 1.0f + position.y, 0.0f + position.z, 1.0f, 1.0f, facesTextureId.BottomFace),
       Vertex(1.0f + position.x, 0.0f + position.y, 0.0f + position.z, 1.0f, 0.0f, facesTextureId.BottomFace),
       Vertex(0.0f + position.x, 1.0f + position.y, 0.0f + position.z, 0.0f, 1.0f, facesTextureId.BottomFace),
    };
    vertices.insert(vertices.end(), insertVertex, insertVertex + 4);
}
void Block::FrontFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position)
{
    indices.reserve(6);
    int latestIndex = 0;
    if (indices.size() > 0)
    {
        latestIndex += indices.back() + 1;
    }
    int insertIndices[6] = { latestIndex,latestIndex + 1,latestIndex + 2,latestIndex + 1,latestIndex,latestIndex + 3 };
    indices.insert(indices.end(), insertIndices, insertIndices + 6);
    vertices.reserve(4);
    Vertex insertVertex[4] = {
        Vertex(0.0f + position.x, 0.0f + position.y, 1.0f + position.z, 0.0f, 0.0f, facesTextureId.FrontFace),
        Vertex(1.0f + position.x, 1.0f + position.y, 1.0f + position.z, 1.0f, 1.0f, facesTextureId.FrontFace),
        Vertex(1.0f + position.x, 0.0f + position.y, 1.0f + position.z, 1.0f, 0.0f, facesTextureId.FrontFace),
        Vertex(0.0f + position.x, 1.0f + position.y, 1.0f + position.z, 0.0f, 1.0f, facesTextureId.FrontFace),
    };
    vertices.insert(vertices.end(), insertVertex, insertVertex + 4);
}
void Block::LeftFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position)
{
    indices.reserve(6);
    int latestIndex = 0;
    if (indices.size() > 0)
    {
        latestIndex += indices.back() + 1;
    }
    int insertIndices[6] = { latestIndex,latestIndex + 1,latestIndex + 2,latestIndex + 1,latestIndex,latestIndex + 3 };
    indices.insert(indices.end(), insertIndices, insertIndices + 6);
    vertices.reserve(4);
    Vertex insertVertex[4] = {
        Vertex(0.0f + position.x, 1.0f + position.y, 1.0f + position.z, 1.0f, 1.0f, facesTextureId.LeftFace),
        Vertex(0.0f + position.x, 0.0f + position.y, 0.0f + position.z, 0.0f, 0.0f, facesTextureId.LeftFace),
        Vertex(0.0f + position.x, 1.0f + position.y, 0.0f + position.z, 0.0f, 1.0f, facesTextureId.LeftFace),
        Vertex(0.0f + position.x, 0.0f + position.y, 1.0f + position.z, 1.0f, 0.0f, facesTextureId.LeftFace),
    };
    vertices.insert(vertices.end(), insertVertex, insertVertex + 4);
}
void Block::RightFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position)
{
    indices.reserve(6);
    int latestIndex = 0;
    if (indices.size() > 0)
    {
        latestIndex += indices.back() + 1;
    }
    //int insertIndices[6] = { latestIndex,latestIndex + 1,latestIndex + 2,latestIndex + 2,latestIndex+3,latestIndex };
    int insertIndices[6] = { latestIndex,latestIndex + 1,latestIndex + 2,latestIndex + 1,latestIndex,latestIndex + 3 };
    indices.insert(indices.end(), insertIndices, insertIndices + 6);
    vertices.reserve(4);
    Vertex insertVertex[4] = {
        Vertex(1.0f + position.x, 1.0f + position.y, 1.0f + position.z, 1.0f, 1.0f, facesTextureId.RightFace),
        Vertex(1.0f + position.x, 0.0f + position.y, 0.0f + position.z, 0.0f, 0.0f, facesTextureId.RightFace),
        Vertex(1.0f + position.x, 1.0f + position.y, 0.0f + position.z, 0.0f, 1.0f, facesTextureId.RightFace),
        Vertex(1.0f + position.x, 0.0f + position.y, 1.0f + position.z, 1.0f, 0.0f, facesTextureId.RightFace),

    };
    vertices.insert(vertices.end(), insertVertex, insertVertex + 4);

}
void Block::BottomFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices, glm::ivec3 position)
{
    indices.reserve(6);
    int latestIndex = 0;
    if (indices.size() > 0)
    {
        latestIndex += indices.back() + 1;
    }
    int insertIndices[6] = { latestIndex,latestIndex + 1,latestIndex + 2,latestIndex + 1,latestIndex,latestIndex +3 };
    indices.insert(indices.end(), insertIndices, insertIndices + 6);
    vertices.reserve(6);
    Vertex insertVertex[4] = {
       Vertex(0.0f + position.x, 0.0f + position.y, 0.0f + position.z, 0.0f, 1.0f, facesTextureId.BottomFace),
       Vertex(1.0f + position.x, 0.0f + position.y, 1.0f + position.z, 1.0f, 0.0f, facesTextureId.BottomFace),
       Vertex(1.0f + position.x, 0.0f + position.y, 0.0f + position.z, 1.0f, 1.0f, facesTextureId.BottomFace),
       Vertex(0.0f + position.x, 0.0f + position.y, 1.0f + position.z, 0.0f, 0.0f, facesTextureId.BottomFace),
    };
    vertices.insert(vertices.end(), insertVertex, insertVertex + 4);
}
void Block::TopFaceMeshData(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices,glm::ivec3 position )
{
    indices.reserve(6);
    int latestIndex = 0;
    if (indices.size() > 0)
    {
        latestIndex += indices.back() + 1;
    }
    int insertIndices[6] = { latestIndex,latestIndex + 1,latestIndex + 2,latestIndex + 1,latestIndex,latestIndex + 3 };
    indices.insert(indices.end(), insertIndices, insertIndices + 6);
    vertices.reserve(4);
    Vertex insertVertex[4] = {
       Vertex(0.0f + position.x, 1.0f + position.y, 0.0f + position.z, 0.0f, 1.0f, facesTextureId.TopFace),
       Vertex(1.0f + position.x, 1.0f + position.y, 1.0f + position.z, 1.0f, 0.0f, facesTextureId.TopFace),
       Vertex(1.0f + position.x, 1.0f + position.y, 0.0f + position.z, 1.0f, 1.0f, facesTextureId.TopFace),
       Vertex(0.0f + position.x, 1.0f + position.y, 1.0f + position.z, 0.0f, 0.0f, facesTextureId.TopFace),
    };
    vertices.insert(vertices.end(), insertVertex, insertVertex + 4);
}

void Block::generateMesh(std::vector<uint32_t>& indices, std::vector<Vertex>& vertices,  SolidNeighBours neighbours, glm::ivec3 position)
{
    if (!neighbours.neighbours[8])
    {
        RightFaceMeshData(indices, vertices, position);
    }

    if (!neighbours.neighbours[17])
    {
           LeftFaceMeshData(indices, vertices,position);

    }
    if (!neighbours.neighbours[2])
    {

            TopFaceMeshData(indices, vertices, position);
            
    }
    if (!neighbours.neighbours[5])
    {

            BottomFaceMeshData(indices, vertices, position);

    }
    if (!neighbours.neighbours[0])
    {

            FrontFaceMeshData(indices, vertices, position);
    }
    if (!neighbours.neighbours[1])
    {

            BackFaceMeshData(indices, vertices,position);
        
    }
}



