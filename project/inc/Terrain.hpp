#pragma once

#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h> // Include Vulkan headers
#include <map>
#include <iostream>
#include "chunk.hpp"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;

    Vertex(float x, float y, float z) : pos(x, y, z), color(1.0f, 1.0f, 1.0f) {}
    Vertex(glm::vec3 position) : pos(position), color(1.0f, 1.0f, 1.0f) {}
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

class Terrain {
public:
    Terrain();
    const std::vector<Vertex>& getVertices() const;
    const std::vector<uint16_t>& getIndices() const;
    void addCube(float x, float y, float z);
    void addChunk(const Chunk& chunk, int chunkX, int chunkY);
    void updateChunks(const glm::vec3 &playerPosition);
    void generateChunksAroundPlayer(const glm::vec3 &playerPosition);
    void removeDistantChunks(const glm::vec3 &playerPosition);

private:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    std::map<std::pair<int, int>, Chunk> chunks;
    int renderDistance = 4;
    std::vector<std::vector<Chunk>> chunkArray;
};