#include "ThreadPool.h"
#include "EngineState.h"
#include <Log.h>
#include <cstdio>
#include <thread>
#include <string>
#include <sstream>

void NV::Threading::ThreadPool::StartUpThread()
{
    std::thread* newThread = new std::thread(&NV::Threading::ThreadPool::ThreadMainFunction, this, m_Threads.size());
    m_Threads.push_back(newThread);
}

void NV::Threading::ThreadPool::ThreadMainFunction(int id)
{
    m_ActiveThreads++;
    std::ostringstream stream;
    stream << "Thread:" << id << " Started.";
    Debug::Log::LogMessage(stream.str());
    while (true)
    {
        ThreadJob* CurrentJob = nullptr;
        bool JobPickedUp = false;
        if (m_Jobs.size() > 0)
        {
            m_JobQueueMutex.lock();
            try
            {
                if (m_Jobs.size() > 0)
                {
                    CurrentJob = m_Jobs.front();
                    m_Jobs.pop();
                    JobPickedUp = true;
                }
            }
            catch (...)
            {

            }
            m_JobQueueMutex.unlock();
            if (JobPickedUp)
            {
                try
                {
                    CurrentJob->ExecutedFunction();
                }
                catch (...)
                {
                    CurrentJob->RunSuccessfully = false;
                }
                if (CurrentJob->CleanOnFinish)
                {
                    delete CurrentJob;
                }
                CurrentJob->Completed = true;
            }
        }
        if (m_ActiveThreads > m_TargetThreadCount)
        {
            break; //Toomany active threads shutting this one down.
        }
        //checking if engine is shutting down and closing the thread after last work package was handled.
        if (!m_EngineState->GetIsRunning() && m_Jobs.size() == 0)
        {
            break; 
        }
    }
    m_ActiveThreads--;
}

NV::Threading::ThreadPool::ThreadPool(Core::EngineState* engineState, int ThreadCount)
{
    m_EngineState = engineState;
    printf("ThreadPool Initialized!\n");
    if (ThreadCount == -1)
    {
        //AllowAllocation = true;
        int CoreCount = std::thread::hardware_concurrency();
        if (CoreCount > 1) CoreCount--;
        m_TargetThreadCount = CoreCount;
        ThreadCount = CoreCount;
        printf("%i Cores Found\n", CoreCount);
        if (CoreCount == 1)
        {
            printf("Not enough cores found for Multithreading. Executing Jobs Inline!\n", CoreCount);
            ExecuteInline = true;
            return; //ThreadSetup not needed
        }
    }
    for (size_t i = 0; i < ThreadCount; i++)
    {
        StartUpThread();
    }
}

NV::Threading::ThreadPool::~ThreadPool()
{
    while (m_Threads.size() > 0)
    {
        if (m_Threads.front()->joinable())
        {
            m_Threads.front()->join();
        }
        delete m_Threads.front();
        m_Threads.pop_front();
    }
}

void NV::Threading::ThreadPool::PostJob(ThreadJob * Job)
{
    if (ExecuteInline)
    {
        try
        {
            Job->ExecutedFunction();
        }
        catch (...)
        {
            Job->RunSuccessfully = false;
        }
        Job->Completed = true;
        if (Job->CleanOnFinish)
        {
            delete Job;
        }
        return;
    }

    if (m_ActiveThreads <= 0)
    {
        StartUpThread();
    }
    m_Jobs.push(Job);
}

unsigned int NV::Threading::ThreadPool::GetActiveThreads()
{
    return m_ActiveThreads;
}
