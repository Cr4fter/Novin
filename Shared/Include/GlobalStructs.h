#pragma once
#pragma region Internal Includes 
#include "GlobalEnums.h"
#pragma endregion //Internal Includes
#pragma region External Includes
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#pragma endregion //External Includes

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
			uint32_t RendererIndex;
		};

		struct RawTexData {
			int32_t Width; 
			int32_t Height; 
			int32_t TexChannels;
			void* Pixels;
			~RawTexData()
			{
				delete Pixels;
			}
		};

		struct RawMaterialData {
			RawTexData DiffuseData; 
			RawTexData NormalData;
		};

		struct ShaderDesc
		{
			const char* ShaderCode;
			uint32_t ShaderSize;
			EShaderType Type;
			EShaderLang Language;
		};

		struct ShaderPack {
			std::string ShaderName;
			ShaderDesc VertexShader; 
			ShaderDesc FragShader;
			uint32_t RendererIndex;
			EShaderFormat GetFormat() const {
			}
		};
		struct Transform
		{
			glm::vec3 Position; 
			glm::vec3 Scale; 
			glm::quat Rotation;
		};
	}
}