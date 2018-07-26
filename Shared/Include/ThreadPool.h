#pragma once
namespace NV {
    namespace Core {
        class EngineState;
    }
}

namespace NV
{
    namespace Threading
    {
        class ThreadPool
        {
            Core::EngineState* m_EngineState = nullptr;
        public:
            void Init(Core::EngineState*);
        };
    }
}
