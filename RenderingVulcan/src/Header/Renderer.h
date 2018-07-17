#pragma once
#include "IRendering.h"

namespace NV
{
    namespace Rendering
    {
        class Renderer : public IRendering::IRenderer
        {
            void Init() override;
        };
    }
}
