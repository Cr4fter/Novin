#include "Log.h"


namespace NV
{
    namespace Debug
    {

        Log& Log::GetLogInstance()
        {
            static Log m_LogInstance;
            return m_LogInstance;
        }
        void Log::SetUpLogInstance()
        {
            // m_LogInstance = this;
        }

        void Log::LogMessage(std::string Message)
        {
            GetLogInstance().LogMessageI(Message);
        }
        void Log::LogWarning(std::string Message)
        {
            GetLogInstance().LogWarningI(Message);
        }
        void Log::LogError(std::string Message)
        {
            GetLogInstance().LogErrorI(Message);
        }

        void Log::LogMessageI(std::string Message)
        {
            LogMessageStruct* msg = new LogMessageStruct;
            msg->Message = Message;
            msg->Severity = LogSeverity::Message;

            m_MessageQueue.push(msg);
        }
        void Log::LogWarningI(std::string Message)
        {
            LogMessageStruct* msg = new LogMessageStruct;
            msg->Message = Message;
            msg->Severity = LogSeverity::Warning;

            m_MessageQueue.push(msg);
        }
        void Log::LogErrorI(std::string Message)
        {
            LogMessageStruct* msg = new LogMessageStruct;
            msg->Message = Message;
            msg->Severity = Error;

            m_MessageQueue.push(msg);
        }

        void Log::HandleUpdate()
        {
            GetLogInstance().HandleUpdateI();
        }

        void Log::HandleUpdateI()
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

    }
}
