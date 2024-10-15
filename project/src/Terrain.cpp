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
    // Define the vertices of the cube
    std::vector<Vertex> cubeVertices = {
        {x, y, z}, {x + 1, y, z}, {x + 1, y + 1, z}, {x, y + 1, z}, // Front face
        {x, y, z + 1}, {x + 1, y, z + 1}, {x + 1, y + 1, z + 1}, {x, y + 1, z + 1} // Back face
    };

    // Offset the indices by the current number of vertices
    uint16_t offset = static_cast<uint16_t>(vertices.size());

    // Define the indices for the cube
    std::vector<uint16_t> cubeIndices = {
        offset + 0, offset + 1, offset + 2, offset + 2, offset + 3, offset + 0,
    };

    // Add the cube's vertices and indices to the terrain's vertices and indices
    vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
    indices.insert(indices.end(), cubeIndices.begin(), cubeIndices.end());
}

void Terrain::addChunk(const Chunk& chunk, int chunkX, int chunkY) {
    std::cout << "Adding chunk at (" << chunkX << ", " << chunkY << ")" << std::endl;
    chunks[{chunkX, chunkY}] = chunk;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            Voxel voxel = chunk.GetVoxelByLocalCoordinate(x, y);
            addCube(voxel.Get_x(), voxel.Get_y(), voxel.Get_z());
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