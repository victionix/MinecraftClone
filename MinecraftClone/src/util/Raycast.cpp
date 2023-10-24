#include <util/Raycast.h>
#include <Blocks/AllBlocks.h>
#include <glm/common.hpp>

CastResult util::Raycast::rayCast(glm::vec3 pos, glm::vec3 rayDirection)
{
    auto world = World::getInstance();
    
    CastResult result;
    result.dist = 0.0f;
    result.sucess = false;
    result.position = pos;

    glm::ivec3 gridPosition = glm::ivec3(pos);
    
    glm::vec3 sideDist;
    glm::vec3 deltaDist;
    deltaDist.x = (rayDirection.x == 0) ? 1e30 : glm::abs(1 / rayDirection.x);
    deltaDist.y = (rayDirection.y == 0) ? 1e30 : glm::abs(1 / rayDirection.y);
    deltaDist.z = (rayDirection.z == 0) ? 1e30 : glm::abs(1 / rayDirection.z);

    const glm::vec3 step = glm::sign(rayDirection);

    for (uint16_t i = 0; i < 3; i++)
    {
        sideDist[i] = (step[i] < 0) ? (pos[i]-gridPosition[i])* deltaDist[i] : sideDist.x = (gridPosition[i] + 1.0f - pos[i]) * deltaDist[i];
    }
    while (result.dist < m_MaxDistance)
    {
        result.block = world.getBlock(gridPosition);

        if (result.block!=nullptr)
        {
            if (result.block->mesh != BLOCKMESH_NULL)
            {
                result.sucess = true;
                return result;
            }
        }

        float minimumDist = glm::min(sideDist.x, sideDist.y, sideDist.z);
        if (minimumDist == sideDist.x)
        {
            result.dist = sideDist.x;
            sideDist.x += deltaDist.x;
            gridPosition.x += step.x;
        }
        else if (minimumDist == sideDist.y)
        {
            result.dist = sideDist.y;
            sideDist.y += deltaDist.y;
            gridPosition.y += step.y;
        }
        else
        {
            result.dist = sideDist.z;
            sideDist.z += deltaDist.z;
            gridPosition.z += step.z;
        }
        result.position = gridPosition;
    }
    return result;
}
