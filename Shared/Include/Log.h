#pragma once
#include <string>
#include <queue>

namespace NV
{
    namespace Debug
    {
        enum LogSeverity
        {
            Message,
            Warning,
            Error
        };
        struct LogMessageStruct
        {
            LogSeverity Severity;
            std::string Message;
        };

        class Log
        {
            static Log* m_LogInstance;
            std::queue<LogMessageStruct*> m_MessageQueue;

        public:

            static Log& GetLogInstance()
            {
                return *m_LogInstance;
            }
            void SetUpLogInstance()
            {
                m_LogInstance = this;
            }

            static void LogMessage(std::string Message)
            {
                m_LogInstance->LogMessageI(Message);
            }
            static void LogWarning(std::string Message)
            {
                m_LogInstance->LogWarningI(Message);
            }
            static void LogError(std::string Message)
            {
                m_LogInstance->LogErrorI(Message);
            }

            void LogMessageI(std::string Message)
            {
                LogMessageStruct* msg = new LogMessageStruct;
                msg->Message = Message;
                msg->Severity = LogSeverity::Message;

                m_MessageQueue.push(msg);
            }
            void LogWarningI(std::string Message)
            {
                LogMessageStruct* msg = new LogMessageStruct;
                msg->Message = Message;
                msg->Severity = LogSeverity::Warning;

                m_MessageQueue.push(msg);
            }
            void LogErrorI(std::string Message)
            {
                LogMessageStruct* msg = new LogMessageStruct;
                msg->Message = Message;
                msg->Severity = Error;

                m_MessageQueue.push(msg);
            }

            static void HandleUpdate()
            {
                if (m_LogInstance == nullptr)
                {
                    throw std::exception("Loginstance was not setup!");
                }
                m_LogInstance->HandleUpdateI();
            }
            void HandleUpdateI()
            {
                while (!m_MessageQueue.empty())
                {
                    LogMessageStruct* curmsg = m_MessageQueue.front();
                    m_MessageQueue.pop();
                    switch (curmsg->Severity)
                    {
                    case Message:
                        printf("Message - %s\n", curmsg->Message.c_str());
                        break;
                    case Warning:
                        printf("Warning - %s\n", curmsg->Message.c_str());
                        break;
                    case Error:
                        printf("Error - %s\n", curmsg->Message.c_str());
                        break;
                    default:
                        printf("Unknown Severity - %s\n", curmsg->Message.c_str());
                    }
                    delete curmsg;
                }
            }
        };
        Log* Log::m_LogInstance = nullptr;
    }
}
