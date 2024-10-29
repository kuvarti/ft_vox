#pragma once

#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <unordered_map>

class Terrain {
public:
    struct Vertex {
        glm::vec3 position;
    };

    Terrain();
    const std::vector<Vertex>& getVertices() const;
    const std::vector<uint16_t>& getIndices() const;

private:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
};

class Chunk;
class Terrain1 {

private:
	std::unordered_map<glm::vec2, Chunk *> _chunk_list;
};