#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

namespace NV
{
    namespace Tools
    {
        class iniContainer
        {
            void WriteToFile();
            void parse(std::string text);
            std::pair<std::string, std::string> ParseLine(std::string Line);
            std::map<std::string, std::string> mINI;
            std::string mFile;
        public:
            iniContainer(std::string Path, bool AutoSave = false);
            std::string GetValue(std::string Key);
            void InsertValue(bool Save = false);
            void Save();
            void Refresh();
        };
    }
}