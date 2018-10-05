#pragma once
#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <array>
#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\hash.hpp>
#include "RenderingInternEnums.h"

namespace NV
{
	namespace Rendering
	{ 
		struct ShaderModulePack
		{
			void SetShader(VkShaderModule& module, const EShaderType& config)
			{
				PlacedShader |= config;
				switch (config)
				{
				case EShaderType::EVertex:
					VertexShader = module; 
					break; 
				case EShaderType::EFragment: 
					FragShader = module;
					break;
				}
			}
			void RemoveShader(const EShaderType& config)
			{
				if (PlacedShader&config && config != EShaderType::ENone)
				{
					PlacedShader^=config;
					switch (config)
					{
					case EShaderType::EVertex:
						VertexShader = VK_NULL_HANDLE;
						break;
					case EShaderType::EFragment:
						FragShader = VK_NULL_HANDLE;
						break;
					}
				}
				if (config == EShaderType::ENone)
				{
					VertexShader = VK_NULL_HANDLE; 
					FragShader = VK_NULL_HANDLE;
				}
			}
		private: 
			VkShaderModule VertexShader; 
			VkShaderModule FragShader; 
			int32_t PlacedShader; 
		};
		struct Vertex
		{
			glm::vec3 Pos;
			glm::vec3 Color;
			glm::vec2 TexCoord;
			glm::vec3 Normal;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;

			static VkVertexInputBindingDescription GetBindingDescription() {
				VkVertexInputBindingDescription bindingDescription = {};
				bindingDescription.binding = 0;
				bindingDescription.stride = sizeof(Vertex);
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

				return bindingDescription;
			}

			static std::array<VkVertexInputAttributeDescription, 6> GetAttributeDescriptions() {
				std::array<VkVertexInputAttributeDescription, 6> attributeDescriptions = {};

				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[0].offset = offsetof(Vertex, Pos);

				attributeDescriptions[1].binding = 0;
				attributeDescriptions[1].location = 1;
				attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[1].offset = offsetof(Vertex, Color);

				attributeDescriptions[2].binding = 0;
				attributeDescriptions[2].location = 2;
				attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
				attributeDescriptions[2].offset = offsetof(Vertex, TexCoord);

				attributeDescriptions[3].binding = 0;
				attributeDescriptions[3].location = 3;
				attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[3].offset = offsetof(Vertex, Normal);

				attributeDescriptions[4].binding = 0;
				attributeDescriptions[4].location = 4;
				attributeDescriptions[4].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[4].offset = offsetof(Vertex, Tangent);

				attributeDescriptions[5].binding = 0;
				attributeDescriptions[5].location = 5;
				attributeDescriptions[5].format = VK_FORMAT_R32G32B32_SFLOAT;
				attributeDescriptions[5].offset = offsetof(Vertex, Bitangent);

				return attributeDescriptions;
			}

			bool operator==(const Vertex& other) const {
				return Pos == other.Pos && Color == other.Color && TexCoord == other.TexCoord;
			}
		};

		struct MeshData
		{
			VkDevice LogicalDevice;
			std::vector<Vertex> Vertices;
			std::vector<uint32_t> Indices;
			std::vector<glm::vec3> Tangents;
			std::vector<glm::vec3> Bitangents;
			VkBuffer VertexBuffer;
			VkDeviceMemory VertexBufferMemory;
			VkBuffer IndexBuffer;
			VkDeviceMemory IndexBufferMemory;

			void Release()
			{
				vkDeviceWaitIdle(LogicalDevice);

				Vertices.clear();
				Indices.clear();
				Tangents.clear();
				Bitangents.clear();
				vkDestroyBuffer(LogicalDevice, VertexBuffer, nullptr);
				vkFreeMemory(LogicalDevice, VertexBufferMemory, nullptr);
				vkDestroyBuffer(LogicalDevice, IndexBuffer, nullptr);
				vkFreeMemory(LogicalDevice, IndexBufferMemory, nullptr);
			}
		};
	}
}
namespace std {
	template<> struct hash<NV::Rendering::Vertex> {
		size_t operator() (NV::Rendering::Vertex const & vertex) const {
			return ((hash<glm::vec3>()(vertex.Pos) ^
				(hash<glm::vec3>()(vertex.Color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.TexCoord) << 1);
		}
	};
}