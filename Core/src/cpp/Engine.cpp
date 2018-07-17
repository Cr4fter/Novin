#include "Engine.h"
#include <cstdio>
#include <iostream>
#include "IRendering.h"

#if _WIN64
#include <windows.h>
#endif

typedef NV::IRendering::IRenderer*(*GetRenderingInstance)();

void NV::Core::Engine::Init(const std::string ProjectPath)
{
    printf("Engine Init\n");
    printf("Project: %s\n", ProjectPath.c_str());

    link_renderer();

    m_Renderer->Init();

}

void NV::Core::Engine::Run()
{
    printf("Engine Run\n");
}

void NV::Core::Engine::Teardown()
{
    printf("Engine Teardown\n");
}

void NV::Core::Engine::link_renderer()
{
    const HINSTANCE hGetProcIDDLL = LoadLibrary(L"Renderer.dll");

    if (hGetProcIDDLL == nullptr) {
        std::cout << "cannot locate the .dll file" << std::endl;
        throw std::exception("cannot locate Renderer.dll");
    }

    const GetRenderingInstance GetRenderer = reinterpret_cast<GetRenderingInstance>(GetProcAddress(hGetProcIDDLL, "GetRenderer"));

    m_Renderer = GetRenderer();
}
