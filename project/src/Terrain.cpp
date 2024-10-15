#include "Terrain.hpp"

Terrain::Terrain() {
    chunkArray.resize(renderDistance * 2 + 1, std::vector<Chunk>(renderDistance * 2 + 1));
}

const std::vector<Vertex>& Terrain::getVertices() const {
    return vertices;
}

const std::vector<uint16_t>& Terrain::getIndices() const {
    return indices;
}

void Terrain::addCube(float x, float y, float z) {
    // Define the 8 vertices of the cube
    std::array<glm::vec3, 8> cubeVertices = {
        glm::vec3(x, y, z), glm::vec3(x + 1.0f, y, z), glm::vec3(x + 1.0f, y + 1.0f, z), glm::vec3(x, y + 1.0f, z), // Front face
        glm::vec3(x, y, z + 1.0f), glm::vec3(x + 1.0f, y, z + 1.0f), glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f), glm::vec3(x, y + 1.0f, z + 1.0f) // Back face
    };

    // Add vertices to the vertices vector
    for (const auto& pos : cubeVertices) {
        vertices.push_back({pos});
    }

    // Define the indices for the cube
    std::array<uint16_t, 36> cubeIndices = {
        0, 1, 2, 2, 3, 0, // Front face
        1, 5, 6, 6, 2, 1, // Right face
        5, 4, 7, 7, 6, 5, // Back face
        4, 0, 3, 3, 7, 4, // Left face
        4, 5, 1, 1, 0, 4, // Bottom face
        3, 2, 6, 6, 7, 3  // Top face
    };

    // Offset the indices by the current number of vertices
    uint16_t offset = static_cast<uint16_t>(vertices.size() - 8);
    for (const auto& index : cubeIndices) {
        indices.push_back(index + offset);
    }
}

void Terrain::addChunk(const Chunk& chunk, int chunkX, int chunkY) {
    std::cout << "Adding chunk at (" << chunkX << ", " << chunkY << ")" << std::endl;
    chunks[{chunkX, chunkY}] = chunk;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            Voxel voxel = chunk.GetVoxelByLocalCoordinate(x, y);
            addCube(voxel.Get_x(), voxel.Get_z(), voxel.Get_y());
        }
    }
}

void Terrain::updateChunks(const glm::vec3& playerPosition) {
    generateChunksAroundPlayer(playerPosition);
    removeDistantChunks(playerPosition);
}

void Terrain::generateChunksAroundPlayer(const glm::vec3 &playerPosition) {
    int playerChunkX = static_cast<int>(playerPosition.x) / CHUNK_SIZE;
    int playerChunkY = static_cast<int>(playerPosition.y) / CHUNK_SIZE;

    for (int dx = -renderDistance; dx <= renderDistance; ++dx) {
        for (int dy = -renderDistance; dy <= renderDistance; ++dy) {
            int chunkX = playerChunkX + dx;
            int chunkY = playerChunkY + dy;
            if (chunks.find({chunkX, chunkY}) == chunks.end()) {
                std::cout << "Generating chunk at (" << chunkX << ", " << chunkY << ")" << std::endl;
                Chunk newChunk(chunkX * CHUNK_SIZE, chunkY * CHUNK_SIZE);
                addChunk(newChunk, chunkX, chunkY);
                int arrayX = dx + renderDistance;
                int arrayY = dy + renderDistance;
                if (arrayX >= 0 && arrayX < chunkArray.size() && arrayY >= 0 && arrayY < chunkArray[0].size()) {
                    chunkArray[arrayX][arrayY] = newChunk;
                } else {
                    std::cerr << "Error: Chunk array index out of bounds" << std::endl;
                }
            }
        }
    }
}

void Terrain::removeDistantChunks(const glm::vec3 &playerPosition) {
    int playerChunkX = static_cast<int>(playerPosition.x) / CHUNK_SIZE;
    int playerChunkY = static_cast<int>(playerPosition.y) / CHUNK_SIZE;

    for (auto it = chunks.begin(); it != chunks.end();) {
        int chunkX = it->first.first;
        int chunkY = it->first.second;
        if (abs(chunkX - playerChunkX) > renderDistance || abs(chunkY - playerChunkY) > renderDistance) {
            it = chunks.erase(it);
        } else {
            ++it;
        }
    }
}