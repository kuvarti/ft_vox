#pragma once

#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <unordered_map>

#define _CHUNK_LIST std::unordered_map<glm::vec2, Chunk *, Vec2Hash, Vec2Equal>

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

struct Vec2Hash {
	std::size_t operator()(const glm::vec2& vec) const noexcept {
		std::size_t h1 = std::hash<float>{}(vec.x);
		std::size_t h2 = std::hash<float>{}(vec.y);
		// Combine the two hash values using XOR and bit shifting
		return h1 ^ (h2 << 1);
	}
};

// Define equality operator for glm::vec2 (needed by unordered_map)
struct Vec2Equal {
	bool operator()(const glm::vec2& lhs, const glm::vec2& rhs) const noexcept {
		return std::fabs(lhs.x - rhs.x) < std::numeric_limits<float>::epsilon() &&
			   std::fabs(lhs.y - rhs.y) < std::numeric_limits<float>::epsilon();
	}
};

class Chunk;
class Terrain1 {
public:
	Terrain1();
	Terrain1(glm::vec2);
	~Terrain1();

	const Chunk *GetChunkByGlobalPos(glm::vec2) const;

	_CHUNK_LIST GetAllChunks(){ //TODO delete or change this
		return _chunk_list;
	}

	// Return `True` if _chunk_list updated.
	bool UpdateMap(glm::vec2);
	bool UpdateMap(glm::vec3);
private:
	bool _IsPivotMoved(glm::vec2);
	void _InitMap(glm::vec2);

	void _Circle_Fill(int, int, int);

	void _AddChunk(int, int);
	void _RemoveChunk(int, int);

	glm::vec2 _pivot;
	_CHUNK_LIST _chunk_list;
};