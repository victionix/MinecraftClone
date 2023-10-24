#ifndef GLM_IVEC3_HASH_H
#define GLM_IVEC3_HASH_H

#include <glm/glm.hpp>

struct ivec3Hash {
        std::size_t operator()(const glm::ivec3& v) const {
            // You can use any suitable hash function for glm::ivec3 here
            // For simplicity, we will use a simple hash combining the hash of each component
            return  std::hash<int>()(v.x) ^ std::hash<int>()(v.y) ^ std::hash<int>()(v.z);
        }
        bool operator()(glm::ivec3 const& a, glm::ivec3 const& b) const {
            return a == b;
        }
 };

#endif