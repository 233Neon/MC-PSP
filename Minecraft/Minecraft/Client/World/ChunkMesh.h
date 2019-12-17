#pragma once

#include <array>
#include <vector>
#include <mclib/common/Vector.h>

namespace Minecraft::Terrain {

	typedef struct
	{
		unsigned char u, v;
		short x, y, z;
	}__attribute__((packed)) ChunkVertex16;

	enum FaceTypes{
		TYPE_FRONT,
		TYPE_BACK,
		TYPE_LEFT,
		TYPE_RIGHT,
		TYPE_TOP,
		TYPE_BOTTOM
	};

	class ChunkMesh {
	public:
		ChunkMesh();
		~ChunkMesh();

		void addFace(int faceType, const short blockFace[12], std::array<float, 8> texCoords,
			mc::Vector3i chunkPosition,
			mc::Vector3i blockPosition);

		void bufferMesh();

		int faces;

		std::vector<ChunkVertex16> frontVertexData;
		std::vector<ChunkVertex16> backVertexData;
		std::vector<ChunkVertex16> leftVertexData;
		std::vector<ChunkVertex16> rightVertexData;
		std::vector<ChunkVertex16> topVertexData;
		std::vector<ChunkVertex16> bottomVertexData;

		std::vector<ChunkVertex16> frontVertexData2;
		std::vector<ChunkVertex16> backVertexData2;
		std::vector<ChunkVertex16> leftVertexData2;
		std::vector<ChunkVertex16> rightVertexData2;
		std::vector<ChunkVertex16> topVertexData2;
		std::vector<ChunkVertex16> bottomVertexData2;


	};

	struct ChunkMeshCollection
	{
		ChunkMesh solidMesh;
		ChunkMesh waterMesh;
		ChunkMesh floraMesh;
	};
}