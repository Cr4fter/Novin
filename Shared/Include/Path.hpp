#pragma once
#include <string>
#include <sstream>
#include <filesystem>
#if _WIN32 || _WIN64
#include <ShlObj_core.h>
#endif // _WINDOWS_

namespace fs = std::experimental::filesystem;

namespace NV
{
    namespace Tools
    {
        class Path
        {
        public:
            static std::string Combine(std::string Path1, std::string Path2)
            {
#if _WIN32 || _WIN64
                std::string output;
                output += Path1;
                if (Path1[Path1.length() - 1] != '\\')
                {
                    output += "\\";
                }
                output += Path2;
                return output;
#endif // _WINDOWS_
                throw std::exception("UnknownPlatform!");
            }

            static std::string GetPersistantDataPath(std::string ProjectName)
            {
#if _WIN32 || _WIN64
                PWSTR* DocumentsPath = new PWSTR;
                auto test = SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, DocumentsPath);
                if (test != S_OK)
                {
                    throw std::exception("Could not find Path To Documents!");
                }
                std::wstring wstr = *DocumentsPath;


                int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), 0, 0, 0, 0);
                std::string str(len, '\0');
                WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), &str[0], len, 0, 0);
                CoTaskMemFree(*DocumentsPath);

                return Combine(str, Combine("Novin", ProjectName));
#endif
            }

            /**
             * \brief checks if a directory exists.
             * \param dirName_in string to the desired directory.
             * \return weather the directory exists or not.
             */
            static bool dirExists(const fs::path dirName_in)
            {
                return fs::exists(dirName_in);
            }

            static void CreateDir(const fs::path path)
            {
                fs::create_directories(path);
            }
        };
    }
}
