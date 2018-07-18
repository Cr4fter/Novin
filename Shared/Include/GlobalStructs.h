#pragma once
#include <vector>
#include <glm.hpp>
#include <glm/vec3.hpp>
namespace NV
{
	namespace IRendering
	{
		struct RawVertexData
		{
			glm::vec3 Pos;
			glm::vec3 Color;
			glm::vec2 TexCoord;
			glm::vec3 Normal;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
		};

		struct RawMeshData {
			std::vector<RawVertexData> Vertices;
			std::vector<uint32_t> Indices; 
			std::vector<glm::vec3> Tangents; 
			std::vector<glm::vec3> Bitangents;

		};
	}
}