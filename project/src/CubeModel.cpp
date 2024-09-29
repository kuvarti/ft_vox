#include "CubeModel.hpp"

CubeModel::CubeModel() {
    const int gridSize = 16;
    const float cubeSize = 1.0f;
    const float halfCubeSize = cubeSize / 2.0f;

    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            float xOffset = x * cubeSize;
            float yOffset = y * cubeSize;

            // Front face
            vertices.push_back({{-halfCubeSize + xOffset, -halfCubeSize + yOffset, halfCubeSize}});
            vertices.push_back({{halfCubeSize + xOffset, -halfCubeSize + yOffset, halfCubeSize}});
            vertices.push_back({{halfCubeSize + xOffset, halfCubeSize + yOffset, halfCubeSize}});
            vertices.push_back({{-halfCubeSize + xOffset, halfCubeSize + yOffset, halfCubeSize}});
            // Back face
            vertices.push_back({{-halfCubeSize + xOffset, -halfCubeSize + yOffset, -halfCubeSize}});
            vertices.push_back({{halfCubeSize + xOffset, -halfCubeSize + yOffset, -halfCubeSize}});
            vertices.push_back({{halfCubeSize + xOffset, halfCubeSize + yOffset, -halfCubeSize}});
            vertices.push_back({{-halfCubeSize + xOffset, halfCubeSize + yOffset, -halfCubeSize}});
			// Left face
			vertices.push_back({{-halfCubeSize + xOffset, -halfCubeSize + yOffset, -halfCubeSize}});
			vertices.push_back({{-halfCubeSize + xOffset, -halfCubeSize + yOffset, halfCubeSize}});
			vertices.push_back({{-halfCubeSize + xOffset, halfCubeSize + yOffset, halfCubeSize}});
			vertices.push_back({{-halfCubeSize + xOffset, halfCubeSize + yOffset, -halfCubeSize}});
			// Right face
			vertices.push_back({{halfCubeSize + xOffset, -halfCubeSize + yOffset, -halfCubeSize}});
			vertices.push_back({{halfCubeSize + xOffset, -halfCubeSize + yOffset, halfCubeSize}});
			vertices.push_back({{halfCubeSize + xOffset, halfCubeSize + yOffset, halfCubeSize}});
			vertices.push_back({{halfCubeSize + xOffset, halfCubeSize + yOffset, -halfCubeSize}});
			// Top face
			vertices.push_back({{-halfCubeSize + xOffset, halfCubeSize + yOffset, -halfCubeSize}});
			vertices.push_back({{halfCubeSize + xOffset, halfCubeSize + yOffset, -halfCubeSize}});
			vertices.push_back({{halfCubeSize + xOffset, halfCubeSize + yOffset, halfCubeSize}});
			vertices.push_back({{-halfCubeSize + xOffset, halfCubeSize + yOffset, halfCubeSize}});
			// Bottom face
			vertices.push_back({{-halfCubeSize + xOffset, -halfCubeSize + yOffset, -halfCubeSize}});
			vertices.push_back({{halfCubeSize + xOffset, -halfCubeSize + yOffset, -halfCubeSize}});
			vertices.push_back({{halfCubeSize + xOffset, -halfCubeSize + yOffset, halfCubeSize}});
			vertices.push_back({{-halfCubeSize + xOffset, -halfCubeSize + yOffset, halfCubeSize}});
			

            uint16_t baseIndex = static_cast<uint16_t>(vertices.size()) - 8;

            // Front face
            indices.push_back(baseIndex + 0);
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 3);
            indices.push_back(baseIndex + 0);
            // Back face
            indices.push_back(baseIndex + 4);
            indices.push_back(baseIndex + 5);
            indices.push_back(baseIndex + 6);
            indices.push_back(baseIndex + 6);
            indices.push_back(baseIndex + 7);
            indices.push_back(baseIndex + 4);
            // Left face
            indices.push_back(baseIndex + 4);
            indices.push_back(baseIndex + 0);
            indices.push_back(baseIndex + 3);
            indices.push_back(baseIndex + 3);
            indices.push_back(baseIndex + 7);
            indices.push_back(baseIndex + 4);
            // Right face
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 5);
            indices.push_back(baseIndex + 6);
            indices.push_back(baseIndex + 6);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 1);
            // Top face
            indices.push_back(baseIndex + 3);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 6);
            indices.push_back(baseIndex + 6);
            indices.push_back(baseIndex + 7);
            indices.push_back(baseIndex + 3);
            // Bottom face
            indices.push_back(baseIndex + 4);
            indices.push_back(baseIndex + 5);
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 0);
            indices.push_back(baseIndex + 4);
        }
    }
}

const std::vector<CubeModel::Vertex>& CubeModel::getVertices() const {
    return vertices;
}

const std::vector<uint16_t>& CubeModel::getIndices() const {
    return indices;
}