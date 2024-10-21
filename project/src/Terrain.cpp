#include "Terrain.hpp"


Terrain::Terrain() {
	const int gridSize = 16;
	const float cubeSize = 1.0f;
	const float halfCubeSize = cubeSize / 2.0f;

for (int x = 0; x < gridSize; ++x) {
    for (int y = -50; y < 0; ++y) {
        for (int z = 0; z < gridSize; ++z) {
            float xPos = x * cubeSize;
            float yPos = y * cubeSize;
            float zPos = z * cubeSize;

            vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos - halfCubeSize, zPos - halfCubeSize)});
            vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos - halfCubeSize, zPos - halfCubeSize)});
            vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos - halfCubeSize, zPos + halfCubeSize)});
            vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos - halfCubeSize, zPos + halfCubeSize)});
            vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos + halfCubeSize, zPos - halfCubeSize)});
            vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos + halfCubeSize, zPos - halfCubeSize)});
            vertices.push_back(Vertex{glm::vec3(xPos + halfCubeSize, yPos + halfCubeSize, zPos + halfCubeSize)});
            vertices.push_back(Vertex{glm::vec3(xPos - halfCubeSize, yPos + halfCubeSize, zPos + halfCubeSize)});

            uint16_t startIndex = static_cast<uint16_t>(vertices.size() - 8);
            indices.push_back(startIndex);
            indices.push_back(startIndex + 1);
            indices.push_back(startIndex + 2);
            indices.push_back(startIndex);
            indices.push_back(startIndex + 2);
            indices.push_back(startIndex + 3);

            indices.push_back(startIndex + 4);
            indices.push_back(startIndex + 5);
            indices.push_back(startIndex + 6);
            indices.push_back(startIndex + 4);
            indices.push_back(startIndex + 6);
            indices.push_back(startIndex + 7);

            indices.push_back(startIndex);
            indices.push_back(startIndex + 1);
            indices.push_back(startIndex + 5);
            indices.push_back(startIndex);
            indices.push_back(startIndex + 5);
            indices.push_back(startIndex + 4);

            indices.push_back(startIndex + 1);
            indices.push_back(startIndex + 2);
            indices.push_back(startIndex + 6);
            indices.push_back(startIndex + 1);
            indices.push_back(startIndex + 6);
            indices.push_back(startIndex + 5);

            indices.push_back(startIndex + 2);
            indices.push_back(startIndex + 3);
            indices.push_back(startIndex + 7);
            indices.push_back(startIndex + 2);
            indices.push_back(startIndex + 7);
            indices.push_back(startIndex + 6);

            indices.push_back(startIndex + 3);
            indices.push_back(startIndex);
            indices.push_back(startIndex + 4);
            indices.push_back(startIndex + 3);
            indices.push_back(startIndex + 4);
            indices.push_back(startIndex + 7);
        }
    }
}
}

const std::vector<Terrain::Vertex>& Terrain::getVertices() const {
	return vertices;
}

const std::vector<uint16_t>& Terrain::getIndices() const {
	return indices;
}