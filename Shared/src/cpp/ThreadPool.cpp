#include "ThreadPool.h"
#include <cstdio>

void NV::Threading::ThreadPool::Init(Core::EngineState* engineState)
{
    m_EngineState = engineState;
    printf("ThreadPool Initialized!\n");
}

void NV::Threading::ThreadPool::Teardown()
{
}
