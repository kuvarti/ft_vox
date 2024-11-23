#pragma once

#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <unordered_map>

#define _CHUNK_LIST std::unordered_map<glm::vec2, Chunk *, Vec2Hash, Vec2Equal>

struct Vec2Hash {
	std::size_t operator()(const glm::vec2& vec) const noexcept {
		std::size_t h1 = std::hash<float>{}(vec.x);
		std::size_t h2 = std::hash<float>{}(vec.y);
		return h1 ^ (h2 << 1);
	}
};

struct Vec2Equal {
	bool operator()(const glm::vec2& lhs, const glm::vec2& rhs) const noexcept {
		return std::fabs(lhs.x - rhs.x) < std::numeric_limits<float>::epsilon() &&
			   std::fabs(lhs.y - rhs.y) < std::numeric_limits<float>::epsilon();
	}
};

class Chunk;
class Terrain {
public:
	Terrain();
	Terrain(glm::vec2);
	~Terrain();

	const Chunk *GetChunkByGlobalPos(glm::vec2) const;

	_CHUNK_LIST GetAllChunks(){ //TODO delete or change this
		return _chunk_list;
	}

	size_t	GetChunkListSize() const {
		return _chunk_list.size();
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