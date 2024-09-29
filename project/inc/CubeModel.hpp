#pragma once

#include <vector>
#include <glm/glm.hpp>

class CubeModel {
public:
    struct Vertex {
        glm::vec3 position;
    };

    CubeModel();
    const std::vector<Vertex>& getVertices() const;
    const std::vector<uint16_t>& getIndices() const;

private:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
};