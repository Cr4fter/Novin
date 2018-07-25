#pragma once
#include <fstream>
#include <string>
#include <map>
#include <streambuf>

namespace NV
{
    namespace Tools
    {
        class iniContainer
        {
            void WriteToFile(std::string) const;
            void parse(std::string text);
            static std::pair<std::string, std::string> ParseLine(std::string Line);
            std::map<std::string, std::string>* mINI;
            std::string mFile;
            bool mAutoSave = false;
        public:
            iniContainer(std::string Path, bool AutoSave = false);
            ~iniContainer();
            std::string GetValue(std::string Key) const;
            void InsertValue(std::string Key, std::string Value, bool SaveToFile = false) const;
            void Save() const;
            void Refresh();
        };
    }
}