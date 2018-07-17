#include "../Header/Renderer.h"

NV::IRendering::IRenderer* rend = nullptr;
extern "C"
{
    __declspec(dllexport) NV::IRendering::IRenderer* GetRenderer()
    {
        if (rend == nullptr) rend = new NV::Rendering::Renderer();
        return rend;
    }
}