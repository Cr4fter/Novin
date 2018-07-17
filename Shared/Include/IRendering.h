#pragma once
namespace NV
{
    namespace IRendering
    {
        class IRenderer
        {
        public:
            virtual ~IRenderer() = default;
            virtual void Init() = 0;
        };
    }
}