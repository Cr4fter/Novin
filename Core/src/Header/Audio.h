#pragma once

namespace NV {

}

namespace NV {
    namespace Core {
        class EngineState;
    }
    namespace Threading {
        class ThreadPool;
    }
}

namespace NV
{
    namespace Audio
    {
        class Audio
        {
            Core::EngineState* m_EngineState = nullptr;
            Threading::ThreadPool* m_ThreadPool = nullptr;
        public:
            void Initialize(Core::EngineState*, Threading::ThreadPool*);
        };
    }
}
