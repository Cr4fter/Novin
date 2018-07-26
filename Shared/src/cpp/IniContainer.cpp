#include "iniContainer.h"
#include <algorithm>

NV::Tools::iniContainer::iniContainer(const std::string path, bool AutoSave) : mAutoSave(AutoSave), mFile(path)
{
    mINI = new std::map<std::basic_string<char>, std::basic_string<char>>();
    Refresh();
}

NV::Tools::iniContainer::~iniContainer()
{
    delete mINI;
}

void NV::Tools::iniContainer::Refresh()
{
    std::ifstream file(mFile);
    const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    parse(content);
}

void NV::Tools::iniContainer::parse(const std::string text)
{
    std::string line;
    for (char i : text)
    {
        if (i == '\n')
        {
            mINI->insert(ParseLine(line));
            line.clear();
        }
        else
        {
            line += i;
        }
    }
    if (!line.empty())
    {
        mINI->insert(ParseLine(line));
    }
}

std::pair<std::string, std::string> NV::Tools::iniContainer::ParseLine(const std::string Line)
{
    std::string Key;
    std::string Value;
    bool isKey = true;
    for (const char i : Line)
    {
        if (isKey)
        {
            if (i == ':')
            {
                isKey = false;
                continue;
            }
            Key += i;
        }
        else
        {
            Value += i;
        }
    }

    return std::pair<std::string, std::string>(Key, Value);
}

std::string NV::Tools::iniContainer::GetValue(std::string Key) const
{
    return (*mINI)[Key];
}

void NV::Tools::iniContainer::Save() const
{
    std::string output;
    for (auto it = mINI->begin(); it != mINI->end(); ++it)
    {
        output += it->first;
        output += ":";
        output += it->second;
        output += "\n";
    }
    WriteToFile(output);
}

void NV::Tools::iniContainer::WriteToFile(const std::string content) const
{
    std::fstream writer(mFile);
    writer.setf(std::ios_base::trunc);
    writer.write(content.c_str(), content.length());
    writer.close();
}

void NV::Tools::iniContainer::InsertValue(std::string Key, std::string Value, bool SaveToFile) const
{
    std::replace(Key.begin(), Key.end(), ':', '\0');
    std::replace(Key.begin(), Key.end(), '\n', '\0');

    std::replace(Value.begin(), Value.end(), ':', '\0');
    std::replace(Value.begin(), Value.end(), '\n', '\0');

    (*mINI)[Key] = Value;

    if (SaveToFile || mAutoSave)
    {
        Save();
    }
}
