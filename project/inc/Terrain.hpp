#pragma once

#include <vector>
#include <glm/glm.hpp>

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