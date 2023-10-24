#ifndef GLM_IVEC3_HASH_H
#define GLM_IVEC3_HASH_H

#include <glm/glm.hpp>

namespace std {
    template <>
    struct hash<glm::ivec3> {
        std::size_t operator()(const glm::ivec3& v) const {
            // You can use any suitable hash function for glm::ivec3 here
            // For simplicity, we will use a simple hash combining the hash of each component
            std::size_t h1 = std::hash<int>()(v.x);
            std::size_t h2 = std::hash<int>()(v.y);
            std::size_t h3 = std::hash<int>()(v.z);
            return h1 ^ (h2) ^ (h3);
        }
        bool operator()(glm::ivec3 const& a, glm::ivec3 const& b) const {
            return a == b;
        }
    };
}


#endif