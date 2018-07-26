#include "../Header/Audio.h"
#include "ThreadPool.h"
#include <cstdio>

void NV::Audio::Audio::Initialize(Core::EngineState* engineState, Threading::ThreadPool* tpool)
{
    m_EngineState = engineState;
    m_ThreadPool = tpool;
    printf("Audio Initialized!\n");
}
