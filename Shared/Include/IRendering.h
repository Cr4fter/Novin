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
            virtual void Init() = 0;
			virtual void Run() = 0;
			virtual void ApplyRawMeshData(RawMeshData& meshData) = 0;
			virtual void Release() = 0;
        };
    }
}