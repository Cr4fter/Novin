#pragma once
#include <vector>
#include <glm\vec3.hpp>
#include "RenderingInternStructs.h"

namespace NV
{
	namespace Rendering
	{
		class RendererStorage
		{
		private: 
			std::vector<MeshData> m_meshes;
		public: 
			uint32_t StoreMesh(MeshData mesh);
			bool RemoveMesh(const uint32_t& index);
			uint32_t StoreMaterial(); 

		};
	}
}