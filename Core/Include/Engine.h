#pragma once
#include <string>

namespace NV {
    namespace IRendering {
        class IRenderer;
    }
}

namespace NV
{
    namespace Core
    {
        class Engine
        {
        public:
            void Init(std::string);
            void Run();
            void Teardown();
        private:
            void link_renderer();

            IRendering::IRenderer* m_Renderer = nullptr;
        };
    }
}
