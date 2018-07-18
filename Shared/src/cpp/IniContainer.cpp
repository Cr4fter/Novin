#include "iniContainer.h"

void NV::Tools::iniContainer::WriteToFile()
{
}

void NV::Tools::iniContainer::parse(std::string text)
{
}

std::pair<std::string, std::string> NV::Tools::iniContainer::ParseLine(std::string Line)
{
    std::pair<std::string, std::string> output;
    for (int i = 0; i < Line.length(); i++)
    {
    }

}

NV::Tools::iniContainer::iniContainer(const std::string Path, bool AutoSave)
{
    mFile = Path;
    std::ifstream file(Path);
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    std::cout << content << std::endl;

    for (int i = 0; i < content.length(); i++)
    {
        std::string line;
        if (content[i] == '\n')
        {
            
        }
    }

    mINI.insert(std::pair<std::string, std::string>("Hallo", "Welt"));
    std::cout << mINI["Hallo"] << std::endl;
}

std::string NV::Tools::iniContainer::GetValue(std::string Key)
{
    return mINI[Key];
}

void NV::Tools::iniContainer::InsertValue(bool Save)
{
}

void NV::Tools::iniContainer::Save()
{
}

void NV::Tools::iniContainer::Refresh()
{
}
