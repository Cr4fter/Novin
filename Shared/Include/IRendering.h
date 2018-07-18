#pragma once
#include <stdint.h>
#include <GlobalStructs.h>

namespace NV
{
    namespace IRendering
    {
        class IRenderer
        {
        public:
            virtual ~IRenderer() = default;
            virtual void Init(GLFWwindow* wnd) = 0;
			virtual uint32_t GetRawMeshData(RawMeshData& meshData) = 0;

        };
    }
}