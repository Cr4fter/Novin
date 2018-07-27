#pragma once
#include <string>
#include <queue>

#ifdef NV_BUILD_STATIC
#    define NV_EXPORT 
#else 
#ifdef NV_BUILD_DLL
#    define NV_EXPORT __declspec(dllexport)
#else 
#    define NV_EXPORT __declspec(dllimport)
#endif
#endif
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
        class NV_EXPORT Log
        {
            std::queue<LogMessageStruct*> m_MessageQueue;

        public:

            static Log& GetLogInstance();
            void SetUpLogInstance();

            static void LogMessage(std::string Message);
            static void LogWarning(std::string Message);
            static void LogError(std::string Message);

            void LogMessageI(std::string Message);
            void LogWarningI(std::string Message);
            void LogErrorI(std::string Message);

            static void HandleUpdate();
            void HandleUpdateI();
        };
    }
}
