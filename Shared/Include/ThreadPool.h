#pragma once
#include <list>
#include <queue>
#include <memory>
#include <mutex>
#include <atomic>
#include <functional>

namespace NV {
    namespace Core {
        class EngineState;
    }
}

namespace NV
{
    namespace Threading
    {
        struct ThreadJob
        {
            std::function<void(void)> ExecutedFunction;
            bool Completed = false;
            bool RunSuccessfully = true;
            bool CleanOnFinish = true;
        };

        class ThreadPool
        {
            Core::EngineState* m_EngineState = nullptr;
            std::list<std::thread*> m_Threads;
            std::atomic<unsigned int> m_ActiveThreads;
            std::atomic<unsigned int> m_TargetThreadCount = 4;
            std::queue<ThreadJob*> m_Jobs;
            std::mutex m_JobQueueMutex;

            bool ExecuteInline = false;
            bool AllowAllocation = false;

            void StartUpThread();

            void ThreadMainFunction(int id);

        public:
            ThreadPool(Core::EngineState* engineState, int ThreadCount = -1);
            ~ThreadPool();
            void PostJob(ThreadJob* Job);

            unsigned int GetActiveThreads();
        };

    }
}
