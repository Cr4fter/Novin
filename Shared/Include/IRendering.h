#pragma once
#include <stdint.h>
#include <GlobalStructs.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace NV
{
    namespace IRendering
    {
        class IRenderer
        {
        public:
            virtual ~IRenderer() = default;
            virtual void Init(GLFWwindow* wnd, std::vector<ShaderPack> shaders) = 0;
			virtual void Run() = 0;
			virtual uint32_t ApplyRawMeshData(RawMeshData& meshData) = 0;
			virtual void Release() = 0;
        };
    }
}